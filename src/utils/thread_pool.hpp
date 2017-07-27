#include <queue>
#include <atomic>
#include <functional>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <exception>
#include <future>
#include <mutex>
#include <queue>

#pragma once


namespace broccoli
{

  /**
  ** This thread pool is used only for Bin->eval member function
  ** It has a fixed size and can cache results, using the pointer to the AST 
  ** node as a way of identification
  */
  class thread_pool
  {
    protected:
      /// Tasks to be done 
      std::queue<std::function<void()> *> tasks_;

      /// thread groups
      std::vector<std::thread> threads_;
      /// mutex for the pool
      std::mutex mutex_;

      std::condition_variable condition_;
      std::atomic<bool> running_;
      std::atomic<bool> stopped_;
      std::atomic<unsigned> tasks_running_;  // how many tasks are running

    /// @brief Constructor.
    // deleted
    thread_pool(const thread_pool &)= delete;
    thread_pool(thread_pool &&) = delete;
    thread_pool & operator=(const thread_pool &) = delete;
    thread_pool & operator=(thread_pool &&) = delete;
   public:

        thread_pool(int nThreads, bool stopped = false);
        // the destructor waits for all the functions in the queue to be finished
        virtual ~thread_pool();

        // get the number of running threads in the pool
        int size() { return static_cast<int>(this->threads_.size()); }
        bool waiting() { return tasks_running_ == 0; }
        std::thread & get_thread(int i) { return this->threads_[i]; }

        // empty the queue


    void init(bool stopped, unsigned size);

    void stop();

    void resume();


  /// @brief Add task to the queue
  template<typename F, typename... Rest>
  auto push(F && f, Rest&&... rest) ->std::future<decltype(f(rest...))>
  {
   auto pck = std::make_shared<std::packaged_task<decltype(f(rest...))()>>(
                  std::bind(std::forward<F>(f), std::forward<Rest>(rest)...)
                  );
   auto _f = new std::function<void()>([pck]() {
                  (*pck)();
              });

   std::unique_lock<std::mutex> lock(mutex_);
   tasks_.push(_f);
   tasks_running_++;
   condition_.notify_one();
   return pck->get_future();
  }

  /// @brief Add task to the queue
  template<typename F>
  auto push(F && f) ->std::future<decltype(f())>
    {
     auto pck = std::make_shared<std::packaged_task<decltype(f())()>>(
                    std::bind(std::forward<F>(f))
                    );
     auto _f = new std::function<void()>([pck]() {
                       (*pck)();
                   });

     std::unique_lock<std::mutex> lock(mutex_);
     tasks_.push(_f);
     tasks_running_++;
     condition_.notify_one();
     return pck->get_future();
    }

    
  protected:
   /// @brief Entry point for pool threads.
     void pool_main();

  };

}


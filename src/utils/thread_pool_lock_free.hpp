#include <queue>
#include <atomic>
#include <functional>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <map>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include "concurrentqueue.h"
#include "blockingconcurrentqueue.h"

#pragma once

#define BULK_SIZE 100

namespace broccoli
{

  /**
  ** This thread pool is used only for Bin->eval member function
  ** It has a fixed size and can cache results, using the pointer to the AST 
  ** node as a way of identification
  */
  class thread_pool_lock_free
  {
    protected:
      /// Tasks to be done 
      moodycamel::BlockingConcurrentQueue<std::function<void()> *> tasks_;
      /// thread groups
      std::vector<std::thread> threads_;
      std::map<std::thread::id, unsigned> tokens_id;
      std::vector<moodycamel::ConsumerToken> tokens_;
      std::mutex tokens_mutex;


      std::atomic<bool> running_;
      std::atomic<bool> stopped_;
      std::atomic<int> tasks_running_;  // how many tasks are running

    /// @brief Constructor.
    // deleted
    thread_pool_lock_free(const thread_pool_lock_free &)= delete;
    thread_pool_lock_free(thread_pool_lock_free &&) = delete;
    thread_pool_lock_free & operator=(const thread_pool_lock_free &) = delete;
    thread_pool_lock_free & operator=(thread_pool_lock_free &&) = delete;
   public:

        thread_pool_lock_free(int nThreads, bool stopped = false);
        // the destructor waits for all the functions in the queue to be finished
        virtual ~thread_pool_lock_free();

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


   tasks_.enqueue(_f);
   tasks_running_++;
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


     tasks_.enqueue(_f);
     tasks_running_++;
     return pck->get_future();
    }

    
  protected:
   /// @brief Entry point for pool threads.
     void pool_main();

  };

}


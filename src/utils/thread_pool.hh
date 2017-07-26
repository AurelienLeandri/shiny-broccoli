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
    private:
      /// Tasks to be done 
      std::queue<std::function<void()> *> tasks_;

      /// thread groups
      std::vector<std::thread> threads_;
      /// mutex for the pool
      std::mutex mutex_;

      std::condition_variable condition_;
      std::atomic<bool> running_;
      std::atomic<bool> stopped_;
      std::atomic<unsigned> available_;  // how many threads are waiting



   private:

    /// @brief Constructor.
    // deleted
    thread_pool(const thread_pool &)= delete;
    thread_pool(thread_pool &&) = delete;
    thread_pool & operator=(const thread_pool &) = delete;
    thread_pool & operator=(thread_pool &&) = delete;
   public:


        thread_pool() { this->init(std::thread::hardware_concurrency()); }
        thread_pool(int nThreads) { this->init(nThreads); }

        // the destructor waits for all the functions in the queue to be finished
        ~thread_pool() {
            // Set running flag to false then notify all threads.
                {
                  std::unique_lock< std::mutex > lock( mutex_ );
                  running_ = false;
                  condition_.notify_all();
                }

                try
                {
                  for (std::size_t i = 0; i < threads_.size(); ++i)
                     threads_[i].join();
                }
                // Suppress all exceptions.
                catch ( const std::exception& ) {}
        }

        // get the number of running threads in the pool
        int size() { return static_cast<int>(this->threads_.size()); }

        std::thread & get_thread(int i) { return this->threads_[i]; }

        // empty the queue


    void init(unsigned size)
     {
    this->stopped_ = false;
    this->running_ = true;

     threads_.resize(size);
     for ( std::size_t i = 0; i < size; ++i )
        {
          threads_[i] = std::thread(&broccoli::thread_pool::pool_main, this);
        }
    }

    void stop()
    {
    this->stopped_ = true;
    }

    void resume()
    {
      this->stopped_ = false;
    }

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
     condition_.notify_one();
     return pck->get_future();
    }

    
  private:
   /// @brief Entry point for pool threads.
     void pool_main()
     {
       while( running_ )
       {
         // Wait on condition variable while the task is empty and the pool is
         // still running.
         std::unique_lock< std::mutex > lock( mutex_);
         while ((tasks_.empty() || stopped_) && running_)
         {
           condition_.wait( lock );
         }
         // If pool is no longer running, break out.
         if ( !running_ ) break;

         // Copy task locally and remove from the queue.  This is done within
         // its own scope so that the task object is destructed immediately
         // after removing the task from the results map, unless it stays cached.
         // This is useful in the event that the

         // function contains shared_ptr arguments bound via bind.
         {
           std::function< void() >* _task = tasks_.front();
           tasks_.pop();
           std::unique_ptr<std::function<void()>> func(_task); // at return, delete the function even if an exception occurred

           lock.unlock();

           if (!stopped_) // If we are stopped we won't even run the task
           {


           // Run the task.
           try
           {
             (*_task)();
           }
           // Suppress all exceptions.
           catch ( const std::exception& ) {}
           }
         }

         // Task has finished, so increment count of available threads.

       } // while running_
     }
  };

}


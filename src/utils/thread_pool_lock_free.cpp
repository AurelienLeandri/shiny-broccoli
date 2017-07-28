#include <iostream>
#include "thread_pool_lock_free.hpp"


namespace broccoli
{


        thread_pool_lock_free::thread_pool_lock_free(int nThreads, bool stopped )

         { this->init(stopped, nThreads); }

        // the destructor waits for all the functions in the queue to be finished
         thread_pool_lock_free::~thread_pool_lock_free() {
            // Set running flag to false then notify all threads.
                 std::cout << "waiting !\n";

                                while(tasks_running_ > 0)
                                  continue;

                                std::cout << "waited !\n";

                                                  running_ = false;

                                for (std::size_t i = 0; i < threads_.size(); ++i)
                                     threads_[i].join();
        }




    void  thread_pool_lock_free::init(bool stopped, unsigned size)
     {
    this->stopped_ = stopped;
    this->running_ = true;
    this->tasks_running_.store(0);
    
     std::cout << "thread pool created with " << size << " threads" << std::endl;
     threads_.resize(size);
     for ( std::size_t i = 0; i < size; ++i )
        {
          threads_[i] = std::thread(&broccoli::thread_pool_lock_free::pool_main, this);
        }
    }

    void  thread_pool_lock_free::stop()
    {
      this->stopped_ = true;
    }

    void  thread_pool_lock_free::resume()
    {
      this->stopped_ = false;
    }


     /// @brief Entry point for pool threads.
     void  thread_pool_lock_free::pool_main()
     {
        // Consumer token
        {
          std::unique_lock<std::mutex> lock(tokens_mutex);
          //moodycamel::ConsumerToken ptok(tasks_);
          tokens_.emplace_back(tasks_);
          tokens_id.emplace(std::this_thread::get_id(), tokens_.size() - 1);
        }

       while( running_ )
       {
         // Wait on condition variable while the task is empty and the pool is
         // still running.
         std::function< void() >* _task[BULK_SIZE];
         std::size_t size_extracted = 0;
         while ((stopped_ || (size_extracted = tasks_.wait_dequeue_bulk_timed( _task, BULK_SIZE, 100)) == 0)
         && running_)
            continue;
         // If pool is no longer running, break out.
         if ( !running_ ) break;

         // Copy task locally and remove from the queue.  This is done within
         // its own scope so that the task object is destructed immediately
         // after removing the task from the results map, unless it stays cached.
         // This is useful in the event that the

         // function contains shared_ptr arguments bound via bind.

           for (std::size_t i = 0; i < size_extracted; ++i)
           {
             std::unique_ptr<std::function<void()>> func(_task[i]); // at end of scope, delete the function even if an exception occurred

           // Run the task.
           try
           {
             (*_task[i])();
           }
           // Suppress all exceptions.
           catch ( const std::exception& ) {}


           tasks_running_--;
           }

         // Task has finished, so increment count of available threads.

       } // while running_
     }

}


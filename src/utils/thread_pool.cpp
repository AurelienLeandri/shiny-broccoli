#include "thread_pool.hpp"
#include <iostream>

namespace broccoli
{
  thread_pool::thread_pool(int nThreads, bool stopped ) {
    this->init(stopped, nThreads);
  }

  // the destructor waits for all the functions in the queue to be finished
  thread_pool::~thread_pool() {
    // Set running flag to false then notify all threads.

    while(tasks_running_ > 0)
      continue;

    {
      std::unique_lock< std::mutex > lock( mutex_ );
      running_ = false;
      condition_.notify_all();
    }

    for (std::size_t i = 0; i < threads_.size(); ++i)
      threads_[i].join();

  }




  void  thread_pool::init(bool stopped, unsigned size)
  {
    this->stopped_.store(stopped);
    this->running_ = true;
    this->tasks_running_.store(0);

    threads_.resize(size);
    for ( std::size_t i = 0; i < size; ++i )
    {
      threads_[i] = std::thread(&broccoli::thread_pool::pool_main, this);
    }
  }

  void  thread_pool::stop()
  {
    this->stopped_ = true;
    condition_.notify_all();
  }

  void  thread_pool::resume()
  {
    this->stopped_ = false;
    condition_.notify_all();
  }


  /// @brief Entry point for pool threads.
  void  thread_pool::pool_main()
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
      std::function< void() >* _task = tasks_.front();
      tasks_.pop();
      std::unique_ptr<std::function<void()>> func(_task); // at end of scope, delete the function even if an exception occurred

      lock.unlock();

      // Run the task.
      try {
        (*_task)();
      } catch ( const std::exception& ) {} // Delete all exceptions

      tasks_running_--;


      // Task has finished, so increment count of available threads.

    } // while running_
  }

}


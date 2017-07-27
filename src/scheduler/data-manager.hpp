//
// Created by leo on 7/14/17.
//

#pragma once


#include <agent/agent.hpp>
#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include <utils/thread_pool.hpp>
#include <map>
#include "action.hpp"
#include <cstdint>

namespace broccoli {

template <typename T1, typename T2>
class DataUpdate;

  class DataManager {
    public:
      DataManager() : _threads(new broccoli::thread_pool(std::thread::hardware_concurrency(), true)), _use_threads(true) {}
      DataManager(bool use_threads) : _threads(nullptr), _use_threads(use_threads)
	  {
	    if (_use_threads)
		{
		  _threads = new broccoli::thread_pool(std::thread::hardware_concurrency(), true);
		}
	  }
      ~DataManager();

    public:
      void poll_requests();

	  template<typename T>
 	  void add_action(DataUpdate<T, void> *update) {

          if (_use_threads)
          {
		  _threads->push([update]() { update->execute();} );

          _mutex_vector.lock();
		  if (_mutex_cache.find(update->get_data_address()) == _mutex_cache.end())
		    _mutex_cache[update->get_data_address()] = new std::mutex();

          _mutex_vector.unlock();
          }
          else{
            pending_actions.push_back(update);

          if (_mutex_cache.find(update->get_data_address()) == _mutex_cache.end())
          		    _mutex_cache[update->get_data_address()] = new std::mutex();
          }
	  }
      void add_action(Action *action);
      std::mutex *get_mutex(uintptr_t data_address);

    private:
      broccoli::thread_pool *_threads;
      std::vector<Action*> pending_actions;
      std::map<uintptr_t, std::mutex*> _mutex_cache; // TODO: Remove old mutexes to optimize space
      bool _use_threads;
      std::mutex _mutex_vector;
      std::mutex _mutex_actions;
  };

}

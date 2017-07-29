//
// Created by leo on 7/14/17.
//

#pragma once

#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include <iostream>
#include <utils/thread_pool_agent.hpp>
#include <utils/thread_pool_agent_lock_free.hpp>
#include "threading-policy.hpp"
#include "data-manager.hpp"

namespace broccoli {

  class Scheduler {
    public:
      Scheduler(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents,
      std::shared_ptr<DataManager> data_manager)
          : _threads_free(new broccoli::thread_pool_agent_free(agents, std::thread::hardware_concurrency())),
           _agents(agents),
           _use_threads(true), _data_manager(data_manager) , _use_lock(false)
           {}


      Scheduler(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents,
      std::shared_ptr<DataManager> data_manager,
       bool use_threads, LockPolicy lock_policy = LockPolicy::LOCK_FREE)
          : _threads(nullptr), _threads_free(nullptr),
           _agents(agents)
          , _use_threads(use_threads), _data_manager(data_manager),
          _use_lock(lock_policy == LockPolicy::USE_LOCK)
	  {

	    if (_use_threads)
		{

		  if (_use_lock)
	          _threads = new broccoli::thread_pool_agent(agents, std::thread::hardware_concurrency());
		   else
    		  _threads_free = new broccoli::thread_pool_agent_free(agents, std::thread::hardware_concurrency());
		}
	  }

	  ~Scheduler()
	  {
	    if (_threads)
	      delete _threads;
	     if (_threads_free)
	       delete _threads_free;
	  }

    public:
      void start();
      void tick();

    private:

      broccoli::thread_pool_agent_free *_threads_free = nullptr;
      broccoli::thread_pool_agent *_threads = nullptr;
      std::shared_ptr<DataManager> _data_manager;
      bool _use_threads;
      bool _use_lock;
      std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> _agents;
  };

}

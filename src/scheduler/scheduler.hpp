//
// Created by leo on 7/14/17.
//

#pragma once

#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include <utils/thread_pool_agent.hpp>
#include "data-manager.hpp"

namespace broccoli {

  class Scheduler {
    public:
      Scheduler(std::vector<std::pair<unsigned int, Agent *>> &agents, DataManager &data_manager)
          : _agents(agents), _threads(new broccoli::thread_pool_agent(agents, std::thread::hardware_concurrency())), _use_threads(true), _data_manager(data_manager) {}
      Scheduler(std::vector<std::pair<unsigned int, Agent *>> &agents, DataManager &data_manager, bool use_threads)
          : _agents(agents), _threads(nullptr), _use_threads(use_threads), _data_manager(data_manager)
	  {
	    if (_use_threads)
		{
		  _threads = new broccoli::thread_pool_agent(agents, std::thread::hardware_concurrency());
		}
	  }

	  ~Scheduler()
	  {
	    if (_threads)
	      delete _threads;
	  }

    public:
      void start();
      void tick();

    private:

      std::vector<std::pair<unsigned int, Agent *>> &_agents;
      broccoli::thread_pool_agent *_threads;
      DataManager &_data_manager;
      bool _use_threads;

  };

}

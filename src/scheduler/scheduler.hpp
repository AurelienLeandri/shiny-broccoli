//
// Created by leo on 7/14/17.
//

#pragma once

#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include "data-manager.hpp"

namespace broccoli {

  class Scheduler {
    public:
      Scheduler(std::vector<std::pair<unsigned int, Agent *>> &agents, DataManager &data_manager)
          : _agents(agents), _threads(new ctpl::thread_pool(std::thread::hardware_concurrency())), _use_threads(true), _data_manager(data_manager) {}
      Scheduler(std::vector<std::pair<unsigned int, Agent *>> &agents, DataManager &data_manager, bool use_threads)
          : _agents(agents), _use_threads(use_threads), _data_manager(data_manager)
	  {
	    if (_use_threads)
		{
		  _threads = new ctpl::thread_pool(std::thread::hardware_concurrency());
		}
	  }

    public:
      void start();
      void tick();

    private:
      std::vector<std::pair<unsigned int, Agent *>> &_agents;
      ctpl::thread_pool *_threads;
      DataManager &_data_manager;
      bool _use_threads;

  };

}

//
// Created by leo on 7/14/17.
//

#pragma once

#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include <iostream>
#include <utils/thread_pool_agent.hpp>
#include "threading-policy.hpp"
#include "data-manager.hpp"

namespace broccoli {

	class Scheduler {
		public:
			Scheduler(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents,
								std::shared_ptr<DataManager> data_manager)
					: _agents(agents), _use_threads(true), _data_manager(data_manager) {}


			Scheduler(std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> agents,
								std::shared_ptr<DataManager> data_manager,
								bool use_threads, LockPolicy lock_policy = LockPolicy::LOCK_FREE)
					: _threads(nullptr), _agents(agents)
					, _use_threads(use_threads), _data_manager(data_manager)
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

			broccoli::thread_pool_agent *_threads = nullptr;
			std::shared_ptr<DataManager> _data_manager;
			bool _use_threads;
			std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> _agents;
	};

}

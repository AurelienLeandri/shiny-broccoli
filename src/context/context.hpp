//
// Created by leo on 7/15/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/scheduler.hpp>
#include <scheduler/threading-policy.hpp>
#include "environment.hpp"

namespace broccoli {

  class Context {
    public:



      Context();
      Context(ThreadingPolicy threading_policy, LockPolicy lock_policy = LockPolicy::LOCK_FREE);
      virtual ~Context();

    public:
      void add_agent(Agent *agent);
      void add_environment(Environment *environment);
      void start();
      void update();
      DataManager &get_data_manager();

    private:
      std::shared_ptr<DataManager> _data_manager;
      std::shared_ptr<std::vector<std::pair<unsigned int, Agent *>>> _agents;
      std::vector<Environment *> _environments;
      std::shared_ptr<Scheduler> _scheduler;

  };

}

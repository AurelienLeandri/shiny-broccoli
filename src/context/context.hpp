//
// Created by leo on 7/15/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/scheduler.hpp>
#include "environment.hpp"

namespace broccoli {

  class Context {
    public:
      Context() : _scheduler(_agents) {}
      virtual ~Context();

    public:
      void add_agent(Agent *agent);
      void add_environment(Environment *environment);
      void start();

    private:
      DataManager _data_manager;
      std::vector<std::pair<unsigned int, Agent *>> _agents;
      std::vector<Environment *> _environments;
      Scheduler _scheduler;

  };

}

//
// Created by leo on 7/14/17.
//

#pragma once

#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>

namespace broccoli {

  class Scheduler {
    public:
      Scheduler(std::vector<std::pair<unsigned int, Agent *>> &agents) : _agents(agents) {}

    public:
      void start();

    private:
      std::vector<std::pair<unsigned int, Agent *>> &_agents;
      ctpl::thread_pool _threads;

  };

}

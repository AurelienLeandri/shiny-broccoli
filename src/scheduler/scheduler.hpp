//
// Created by leo on 7/14/17.
//

#pragma once


#include <queue>
#include <agent/agent.hpp>
#include "action.hpp"

namespace broccoli {

  class Scheduler : public Agent {
    public:
      Scheduler();

    public:
      void start();
      void step() override;
      void addPending(Action &action);

    private:
      std::queue<Action> pending_actions;
  };

}



//
// Created by leo on 7/14/17.
//

#pragma once


#include <agent/agent.hpp>
#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include "action.hpp"

namespace broccoli {

  class DataManager : public Agent {
    public:
      DataManager();
      ~DataManager();

    public:
      void step() override;
      void addAction(Action *action);

    private:
      ctpl::thread_pool _threads;
      std::vector<Action *> pending_actions;
      std::mutex _mutex;
  };

}



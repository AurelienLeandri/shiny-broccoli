//
// Created by leo on 7/14/17.
//

#pragma once


#include <agent/agent.hpp>
#include <agent/agent.hpp>
#include <utils/ctpl_stl.h>
#include <map>
#include "action.hpp"
#include <cstdint>

namespace broccoli {

  class DataManager : public Agent {
    public:
      DataManager();
      ~DataManager();

    public:
      void step() override;
      void addAction(Action *action);
      std::mutex &getMutex(uintptr_t data_address);

    private:
      ctpl::thread_pool _threads;
      std::vector<Action *> pending_actions;
      std::map<uintptr_t, std::mutex> _mutex_cache; // TODO: Remove old mutexes to optimize space
  };

}



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

  class DataManager {
    public:
      DataManager() : _threads(new ctpl::thread_pool(std::thread::hardware_concurrency())), _use_threads(true) {}
      DataManager(bool use_threads) : _use_threads(use_threads) {}
      ~DataManager();

    public:
      void poll_requests();
      void add_action(Action *action);
      std::mutex &getMutex(uintptr_t data_address);

    private:
      ctpl::thread_pool *_threads;
      std::vector<Action *> pending_actions;
      std::map<uintptr_t, std::mutex> _mutex_cache; // TODO: Remove old mutexes to optimize space
      bool _use_threads;
  };

}



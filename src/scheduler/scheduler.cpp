//
// Created by leo on 7/14/17.
//

#include <future>
#include "scheduler.hpp"
#include <iostream>

namespace broccoli {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  void Scheduler::start() {
    while (true)
       tick();
  }

  void Scheduler::tick() {
    if (_use_threads) {
      std::vector<std::future<void>> results;
      for (unsigned int i = 0; i < _agents.size(); ++i) {
        if (_agents[i].second) {
          _agents[i].first--;
          if (!_agents[i].first && _agents[i].second->is_step_enabled()) {
            results.push_back(_threads->push([this, i]() { _agents[i].second->step(); }));
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
      }

      for (unsigned int i = 0; i < results.size(); ++i)
        if (results[i].valid())
          results[i].get();
    }
    else {
      for (unsigned int i = 0; i < _agents.size(); ++i) {
        if (_agents[i].second) {
          _agents[i].first--;
          if (!_agents[i].first && _agents[i].second->is_step_enabled()) {
            _agents[i].second->step();
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
      }
    }

    _data_manager.poll_requests();
  }

#pragma clang diagnostic pop

}

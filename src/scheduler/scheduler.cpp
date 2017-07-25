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
    if (_use_threads) {
      while (true) {
        std::cout << " -------- ITERATION --------" << std::endl;
        std::vector<std::future<void>> results;
        for (unsigned int i = 0; i < _agents.size(); ++i) {
          _agents[i].first--;
          if (!_agents[i].first) {
            results.push_back(_threads->push([this, i](int) { _agents[i].second->step(); }));
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
        for (unsigned int i = 0; i < results.size(); ++i)
          if (results[i].valid())
            results[i].get();
        _data_manager.poll_requests();
      }
    }
    else {
      while (true) {
        for (unsigned int i = 0; i < _agents.size(); ++i) {
          _agents[i].first--;
          if (!_agents[i].first) {
            _agents[i].second->step();
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
        _data_manager.poll_requests();
      }
    }
  }
#pragma clang diagnostic pop

}

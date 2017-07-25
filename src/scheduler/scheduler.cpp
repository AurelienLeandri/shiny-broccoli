//
// Created by leo on 7/14/17.
//

#include <future>
#include "scheduler.hpp"

namespace broccoli {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  void Scheduler::start() {
    if (_use_threads) {
      while (true) {
        std::vector<std::future<void>> results;
        for (unsigned int i = 0; i < _agents.size(); ++i) {
          if (_agents[i].second) {
            _agents[i].first--;
            if (!_agents[i].first) {
              results.push_back(_threads.push([this, i](int) { _agents[i].second->step(); }));
              _agents[i].first = _agents[i].second->get_ticks_between_updates();
            }
          }
        }
        results.push_back(_threads.push([this](int) { _data_manager.poll_requests(); }));
        for (unsigned int i = 0; i < results.size(); ++i)
          results[i].get();
      }
    }
    else {
      while (true) {
        for (unsigned int i = 0; i < _agents.size(); ++i) {
          if (_agents[i].second) {
            _agents[i].first--;
            if (!_agents[i].first) {
              _agents[i].second->step();
              _agents[i].first = _agents[i].second->get_ticks_between_updates();
            }
          }
        }
        _data_manager.poll_requests();
      }
    }
  }

  void Scheduler::tick() {
    if (_use_threads) {
      std::vector<std::future<void>> results;
      for (unsigned int i = 0; i < _agents.size(); ++i) {
        if (_agents[i].second) {
          _agents[i].first--;
          if (!_agents[i].first) {
            results.push_back(_threads.push([this, i](int) { _agents[i].second->step(); }));
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
      }
      results.push_back(_threads.push([this](int) { _data_manager.poll_requests(); }));
      for (unsigned int i = 0; i < results.size(); ++i)
        results[i].get();
    }
    else {
      for (unsigned int i = 0; i < _agents.size(); ++i) {
        if (_agents[i].second) {
          _agents[i].first--;
          if (!_agents[i].first) {
            _agents[i].second->step();
            _agents[i].first = _agents[i].second->get_ticks_between_updates();
          }
        }
      }
      _data_manager.poll_requests();
    }
  }

#pragma clang diagnostic pop

}

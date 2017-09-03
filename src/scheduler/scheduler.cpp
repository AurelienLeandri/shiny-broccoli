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
      _threads->step();
    }
    else {
      for (auto& elt : *_agents) {
        if (elt.second) {
          elt.first--;
          if (!elt.first && elt.second->is_step_enabled()) {
            elt.second->step();
            elt.first = elt.second->get_ticks_between_updates();
          }
        }
      }
    }

    _data_manager->poll_requests();
  }

#pragma clang diagnostic pop

}

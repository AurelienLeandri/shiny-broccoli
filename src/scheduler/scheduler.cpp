//
// Created by leo on 7/14/17.
//

#include "scheduler.hpp"

namespace broccoli {

  Scheduler::Scheduler() {

  }

  void Scheduler::step() {
    // FIXME: Use threads to manage action and replace following code
    while (pending_actions.size()) {
      auto action = pending_actions.back();
      action.execute();
      pending_actions.pop();
    }
  }

  void Scheduler::start() {
    // FIXME: Add threads and initialize them ?
  }

  void Scheduler::addPending(Action &action) {
    pending_actions.push(action);
  }
}
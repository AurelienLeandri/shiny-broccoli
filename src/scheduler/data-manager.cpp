//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  DataManager::DataManager() {}

  void DataManager::step() {
    // FIXME: Use threads to manage action and replace following code
    while (pending_actions.size()) {
      auto action = pending_actions.back();
      action.execute();
      pending_actions.pop();
    }
  }

  void DataManager::start() {
    // FIXME: Add threads and initialize them ?
  }

  void DataManager::addPending(Action &action) {
    pending_actions.push(action);
  }
}
//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"
#include <thread>

namespace broccoli {

  DataManager::DataManager() : _threads(std::thread::hardware_concurrency()) {

  }

  void DataManager::step() {
    /*
    std::vector<std::future<void>> results(pending_actions.size());
    for (unsigned int j = 0; j < pending_actions.size(); ++j) {
      results[j] = _threads.push(pending_actions[j]->execute());
    }
    for (unsigned int j = 0; j < pending_actions.size(); ++j)
      results[j].get();
     */
  }

  void DataManager::addAction(Action *action) {
    pending_actions.push_back(action);
  }

  DataManager::~DataManager() {
    for (auto p : pending_actions)
      delete p;
  }

}
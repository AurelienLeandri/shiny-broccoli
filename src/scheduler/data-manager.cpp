//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  DataManager::DataManager() : _threads(std::thread::hardware_concurrency()) {

  }

  void DataManager::step() {
    std::vector<std::future<void>> results(pending_actions.size());
    for (unsigned int i = 0; i < pending_actions.size(); ++i)
      results[i] = _threads.push([this, i](int) { this->pending_actions[i]->execute(); });
    for (unsigned int i = 0; i < pending_actions.size(); ++i)
      results[i].get();
  }

  void DataManager::add_action(Action *action) {
    pending_actions.push_back(action);
  }

  DataManager::~DataManager() {
    for (auto p : pending_actions)
      delete p;
  }

  std::mutex &DataManager::getMutex(uintptr_t data_address) {
    return _mutex_cache.at(data_address);
  }

}
//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  void DataManager::poll_requests() {
    if (_use_threads) {
      std::vector<std::future<void>> results(pending_actions.size());
      for (unsigned int i = 0; i < pending_actions.size(); ++i)
        results[i] = _threads->push([this, i](int) { this->pending_actions[i]->execute(); });
      for (unsigned int i = 0; i < pending_actions.size(); ++i)
        results[i].get();
    }
    else {
      for (unsigned int i = 0; i < pending_actions.size(); ++i)
        this->pending_actions[i]->execute();
    }
  }

  void DataManager::add_action(Action *action) {
    pending_actions.push_back(action);
  }

  DataManager::~DataManager() {
    for (auto p : pending_actions)
      delete p;
    if (_threads)
      delete _threads;
  }

  std::mutex &DataManager::getMutex(uintptr_t data_address) {
    return _mutex_cache.at(data_address);
  }

}
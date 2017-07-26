//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  void DataManager::poll_requests() {
    if (_use_threads) {

       _mutex_actions.lock();
      const size_t pending_actions_size = pending_actions.size();
      std::vector<std::future<void>> results(pending_actions_size);

      for (unsigned int i = 0; i < pending_actions_size; ++i)
        results[i] = _threads->push([this, i]() { this->pending_actions[i]->execute(); });
      pending_actions.clear();
      _mutex_actions.unlock();
      for (unsigned int i = 0; i < pending_actions_size; ++i)
        results[i].get();
    }
    else {
      for (unsigned int i = 0; i < pending_actions.size(); ++i)
        this->pending_actions[i]->execute();
	  pending_actions.clear();
    }
  }

  void DataManager::add_action(Action *action) {
    _mutex_actions.lock();
    pending_actions.push_back(action);
    _mutex_actions.unlock();
  }

  DataManager::~DataManager() {
    for (auto p : pending_actions)
      delete p;
    for (auto p : _mutex_cache)
      delete p.second;
    if (_threads)
      delete _threads;
  }

  std::mutex *DataManager::get_mutex(uintptr_t data_address) {
    return _mutex_cache.at(data_address);
  }

}

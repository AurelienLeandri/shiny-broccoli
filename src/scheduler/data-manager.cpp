//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  void DataManager::poll_requests() {
    if (_use_threads) {
        _threads->resume();
        while (!_threads->waiting())
          continue;

      _threads->stop();
    }
    else {
      for (unsigned int i = 0; i < pending_actions.size(); ++i)
        this->pending_actions[i]->execute();
	  pending_actions.clear();
    }
  }

  void DataManager::add_action(Action *action) {
  if (_use_threads)
  {
    std::cout << "add_action called" << std::endl;
    _threads->push([action]() { action->execute();} );
  }
  else
  {
    pending_actions.push_back(action);
  }
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

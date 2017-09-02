//
// Created by leo on 7/14/17.
//

#include "data-manager.hpp"

namespace broccoli {

  void DataManager::poll_requests() {
    if (_use_threads) {

      if (_use_lock)
      {
        _threads->resume();
        while (!_threads->waiting())
          continue;

         _threads->stop();
      }
      else
      {
        _threads_free->resume();
        while (!_threads_free->waiting())
             continue;

        _threads_free->stop();
      }
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
     if (_use_lock)
        _threads->push([action]() { action->execute();} );
     else
        _threads_free->push([action]() { action->execute();} );
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
    if (_threads_free)
      delete _threads_free;
  }

  std::mutex *DataManager::get_mutex(uintptr_t data_address) {
    return _mutex_cache.at(data_address);
  }

}

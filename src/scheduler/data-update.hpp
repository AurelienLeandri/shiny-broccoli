//
// Created by leo on 7/14/17.
//

#pragma once

#include <memory>
#include "action-result.hpp"
#include "data-manager.hpp"

namespace broccoli {

  template <typename T>
  class DataUpdate : public Action {
    public:
      DataUpdate<T>(T &data, T (*operation)(T &), DataManager &data_manager)
          : _data(data), _operation(operation), _data_manager(data_manager)
      {}
      ~DataUpdate() {}


    public:
      void execute() override;
      uintptr_t get_data_address() { return (uintptr_t) &_data; };

    private:
      T &_data;
      T (*_operation)(T &);
      DataManager &_data_manager;
  };

  template <typename T>
  void DataUpdate<T>::execute() {
    auto *mutex = _data_manager.get_mutex((uintptr_t) &_data);
    mutex->lock();
    _operation(_data);
    mutex->unlock();
  }

}


//
// Created by leo on 7/14/17.
//

#pragma once

#include <memory>
#include "action-result.hpp"
#include "data-manager.hpp"

namespace broccoli {

  template <typename T1, typename T2 = void>
  class DataUpdate : public Action {
    public:
      DataUpdate<T1, T2>(T1 &data, T2 param, void (*operation)(T1 &, T2), DataManager &data_manager)
          : _data(data), _param(std::forward<T2>(param)), _operation(operation), _data_manager(data_manager)
      {}
      ~DataUpdate() {}


    public:
      void execute() override;

    public:
      T1 &_data;
      T2 _param;
      void (*_operation)(T1 &, T2);
      DataManager &_data_manager;
  };

  template <typename T1, typename T2>
  void DataUpdate<T1, T2>::execute() {
    auto *mutex = _data_manager.get_mutex((uintptr_t) &_data);
    mutex->lock();
    _operation(_data, _param);
    mutex->unlock();
  }

  template <typename T>
  class DataUpdate<T, void> : public Action {
    public:
      DataUpdate<T>(T &data, void (*operation)(T &), DataManager &data_manager)
          : _data(data), _operation(operation), _data_manager(data_manager)
      {}
      ~DataUpdate() {}


    public:
      void execute() override;
      uintptr_t get_data_address() { return (uintptr_t) &_data; };

    private:
      T &_data;
      void (*_operation)(T &);
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


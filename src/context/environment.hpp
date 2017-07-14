//
// Created by leo on 7/14/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/data-update.hpp>

namespace broccoli {

  class Environment {
    public:
      Environment(DataManager &data_manager) : data_manager(data_manager) {}
      virtual ~Environment() = 0;

    public:
      template <typename T>
      void modify(T &data, T &(*operation)(T &));

      DataManager &data_manager;
  };

  template<typename T>
  void Environment::modify(T &data, T &(*operation)(T &)) {
    data_manager.addAction(new DataUpdate<T>(data, operation));
  }

}


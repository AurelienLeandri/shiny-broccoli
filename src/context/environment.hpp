//
// Created by leo on 7/14/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/environment-data.hpp>

namespace broccoli {

  class Environment {
    public:
      Environment(DataManager &data_manager) : data_manager(data_manager) {}
      virtual ~Environment() = 0;

    public:
      template <typename T>
      EnvironmentData<T> fetchData(T &data);

      DataManager &data_manager;
  };

  template<typename T>
  EnvironmentData<T> Environment::fetchData(T &data) {
    return EnvironmentData<T>(*data, this->data_manager);
  }

}


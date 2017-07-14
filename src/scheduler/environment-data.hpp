//
// Created by leo on 7/14/17.
//

#pragma once

#include "data-manager.hpp"

namespace broccoli {

  template<typename T>
  class EnvironmentData {
    public:
      EnvironmentData<T>(const T &data_address, const DataManager &data_manager)
      : _data_address(data_address), _data_manager(data_manager) {}

      // FIXME: Operator overloading for read/write operations

    private:
      const T &_data_address;
      const DataManager &_data_manager;
  };

}

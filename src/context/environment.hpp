//
// Created by leo on 7/14/17.
//

#pragma once

#include <scheduler/data-manager.hpp>

namespace broccoli {

  class Environment {
    public:
      Environment(DataManager &data_manager) : data_manager(data_manager) {}
      virtual ~Environment() = 0;

      DataManager &data_manager;
  };

}


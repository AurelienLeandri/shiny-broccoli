//
// Created by leo on 7/14/17.
//

#pragma once

#include <scheduler/data-manager.hpp>
#include <scheduler/data-update.hpp>

namespace broccoli {

  class Environment {
    public:
      Environment() {}
      virtual ~Environment() {};

    public:
      template<typename T>
      void modify(T &data, T (*operation)(T &)) {
              _data_manager->add_action<T>(new DataUpdate<T>(data, operation, *_data_manager));
      };
      void set_data_manager(DataManager *data_manager) { _data_manager = data_manager; }


    private:
      DataManager *_data_manager;
      bool threaded;
  };

}


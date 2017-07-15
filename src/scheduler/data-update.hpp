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

    public:
      T &_data;
      T (*_operation)(T &);
      DataManager &_data_manager;
  };


}


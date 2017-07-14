//
// Created by leo on 7/14/17.
//

#pragma once

#include <memory>
#include "action-result.hpp"

namespace broccoli {

  template <typename T>
  class DataUpdate : public Action {
    public:
      DataUpdate<T>(T &data, T &(*operation)(T &)) : _data(data), _operation(operation) {}

    public:
      void execute() override { _data = _operation(_data); }

    public:
      T &_data;
      T &(*_operation)(T &);
  };

}


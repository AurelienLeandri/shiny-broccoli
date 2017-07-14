//
// Created by leo on 7/14/17.
//

#pragma once

#include <memory>
#include "action-result.hpp"

namespace broccoli {

  class Action {
    public:
      virtual void execute() = 0;
  };

}


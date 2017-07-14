//
// Created by leo on 7/14/17.
//

#pragma once

#include <memory>
#include "action-result.hpp"

namespace broccoli {

  class Action {
    using action_p = std::shared_ptr<Action>;

    public:
      Action(action_p child_action, void (*result_callback)(void *, ActionResult));

    public:
      void execute();

    public:
      action_p child_action;
      void (*result_callback)(void *, ActionResult);
      // FIXME: Add threads to manage actions ?
  };

}


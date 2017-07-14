//
// Created by leo on 7/14/17.
//

#include "action.hpp"

namespace broccoli {

  Action::Action(Action::action_p child_action, void (*result_callback)(void *, ActionResult))
      : child_action(child_action), result_callback(result_callback)
  {
  }

  void Action::execute() {

  }

}
//
// Created by leo on 7/14/17.
//

#pragma once


#include <vector>

namespace broccoli {

  class Agent {
    public:
      Agent(unsigned int ticks_between_updates = 1, bool step_enabled = true)
          : _ticks_between_updates(ticks_between_updates), _step_enabled(step_enabled) {}
      virtual ~Agent() {};

    public:
      virtual void step() = 0;

    public:
      unsigned int get_ticks_between_updates() { return _ticks_between_updates; }
      void set_ticks_between_updates(unsigned int value) { _ticks_between_updates = value; }
      bool is_step_enabled() { return _step_enabled; }
      void enable_step(bool value) { _step_enabled = value; }

    protected:
      unsigned int _ticks_between_updates;
      bool _step_enabled;
  };

}



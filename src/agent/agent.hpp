//
// Created by leo on 7/14/17.
//

#pragma once


#include <vector>

namespace broccoli {

  class Agent {
    public:
      Agent() : _ticks_between_updates(1) {}
      Agent(unsigned int ticks_between_updates) : _ticks_between_updates(ticks_between_updates) {}
      virtual ~Agent() {};

    public:
      virtual void step() = 0;

    public:
      unsigned int get_ticks_between_updates() { return _ticks_between_updates; }

    private:
      unsigned int _ticks_between_updates;
  };

}



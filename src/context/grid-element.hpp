//
// Created by leo on 7/16/17.
//

#pragma once

#include <agent/agent.hpp>
#include "grid-point.hpp"

namespace broccoli {

  class GridElement : public Agent {
    public:
      GridElement(GridPoint position);
      GridElement(GridElement &other) : Agent(other.get_ticks_between_updates()), _position(other.get_position()) {}
      GridElement(GridPoint position, bool step_enabled);
      virtual ~GridElement();

    public:
      virtual void step() = 0;

    public:
      const GridPoint &get_position() { return _position; }
      void set_position(GridPoint position) { _position = position; }

    public:
      GridPoint _position;

  };

}

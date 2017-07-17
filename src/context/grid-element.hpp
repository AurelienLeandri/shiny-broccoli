//
// Created by leo on 7/16/17.
//

#pragma once

#include <agent/agent.hpp>
#include "grid-point.hpp"

namespace broccoli {

  class GridElement : public Agent {
    public:
      GridElement(GridPoint position)
          : Agent(1), _position(position){
        _step_enabled = false;
      }

      virtual ~GridElement() = 0;

    public:
      const GridPoint &get_position() { return _position; }
      const GridPoint &set_position() { return _position; }

    private:
      GridPoint _position;

  };

}

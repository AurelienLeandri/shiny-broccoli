//
// Created by leo on 7/16/17.
//

#include "grid-element.hpp"

namespace broccoli {

  GridElement::GridElement(GridPoint position)
  : Agent(1), _position(position){
      _step_enabled = false;
  }

  GridElement::GridElement(GridPoint position, bool step_enabled)
  : Agent(1), _position(position) {
    _step_enabled = true;
  }

  GridElement::~GridElement() {

  }

}

//
// Created by leo on 7/16/17.
//

#ifndef SHINYBROCCOLI_GRIDPOINT_HPP
#define SHINYBROCCOLI_GRIDPOINT_HPP

namespace broccoli {

  struct GridPoint {
    GridPoint(unsigned int x, unsigned int y) : _x(x), _y(y) {}
    unsigned int _x;
    unsigned int _y;
  };

}

#endif //SHINYBROCCOLI_GRIDPOINT_HPP

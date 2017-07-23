//
// Created by leo on 7/17/17.
//

#pragma once

#include <context/grid.hpp>
#include "grid-tile.hpp"

namespace game {

  class GameGrid : public broccoli::Grid {
    public:
      GameGrid(unsigned int rows, unsigned int cols);
      void load_from_file(const char *file);
      const GridTile &getTile(int x, int y);

    public:
      std::vector<GridTile> _grid_tiles;
  };

}



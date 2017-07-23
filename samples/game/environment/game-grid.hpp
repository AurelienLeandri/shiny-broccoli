//
// Created by leo on 7/17/17.
//

#pragma once

#include <context/grid.hpp>
#include <game/resources-manager.hpp>
#include "grid-tile.hpp"

namespace game {

  class GameGrid : public broccoli::Grid {
    public:
      GameGrid(unsigned int rows, unsigned int cols);
      static GameGrid load_from_file(const char *file, ResourcesManager &rm);
      const GridTile &getTile(int x, int y);

    public:
      std::vector<GridTile> _grid_tiles;

  };

}



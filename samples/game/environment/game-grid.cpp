//
// Created by leo on 7/17/17.
//

#include "game-grid.hpp"

namespace game {

  game::GameGrid::GameGrid(unsigned int rows, unsigned int cols) : Grid(rows, cols) {}

  void game::GameGrid::load_from_file(const char *file) {

  }

  const game::GridTile &game::GameGrid::getTile(int x, int y) {
    return _grid_tiles[y * _cols + x];
  }

}

//
// Created by leo on 7/17/17.
//

#include "game-grid.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace game {

  game::GameGrid::GameGrid(unsigned int rows, unsigned int cols) : Grid(rows, cols) {}

  GameGrid game::GameGrid::load_from_file(const char *file, ResourcesManager &rm) {
    std::ifstream infile(file);
    std::string line;
    unsigned int cols, rows;
    infile >> cols;
    infile >> rows;
    std::getline(infile, line);
    GameGrid grid(rows, cols);
    unsigned int x = 0, y = 0;
    while (std::getline(infile, line)) {
      std::istringstream iss(line);
      int tile_nb;
      while ((iss >> tile_nb)) {
        grid._grid_tiles.push_back(GridTile(broccoli::GridPoint(x, y), TileType(tile_nb),
                                            rm.textures.at(GridTile::getTextureNameForType(TileType(tile_nb)))));
        x++;
      }
      y++;
      x = 0;
    }
    return grid;
  }

  const game::GridTile &game::GameGrid::getTile(int x, int y) {
    return _grid_tiles[y * _cols + x];
  }

  void GameGrid::draw(sf::RenderWindow &target_window) {
    for (auto &e : _grid_tiles)
      e.draw(target_window);
  }

}

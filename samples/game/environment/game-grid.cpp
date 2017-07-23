//
// Created by leo on 7/17/17.
//

#include "game-grid.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <game/constants.hpp>
#include <game/agent/good.hpp>
#include <game/agent/evil.hpp>

namespace game {

  game::GameGrid::GameGrid(unsigned int rows, unsigned int cols) : Grid(rows, cols) {
  }

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

  const game::GridTile &game::GameGrid::get_tile(int x, int y) {
    return _grid_tiles[y * _cols + x];
  }

  void GameGrid::draw(sf::RenderWindow &target_window) {
    for (auto &e : _grid_tiles)
      e.draw(target_window);
    for (auto &e : _grid_elements) {
      for (broccoli::GridElement *f : e) {
        Drawable *drawable = dynamic_cast<Drawable *>(f);
        if (drawable)
          drawable->draw(target_window);
      }
    }
  }

  void GameGrid::load_agents(ResourcesManager &rm) {
    unsigned int x, y;
    for (int i = 0; i < NB_GOOD; i++) {
      x = rand() % _cols;
      y = rand() % _rows;
      std::cout << _grid_elements.size() << std::endl;
      std::cout << "BOUBOU" << y * _cols + x << std::endl;
      _grid_elements[y * _cols + x].push_back(new Good(broccoli::GridPoint(x, y), rm.textures.at("agent_good")));
    }
    for (int i = 0; i < NB_EVIL; i++) {
      x = rand() % _cols;
      y = rand() % _rows;
      _grid_elements[y * _cols + x].push_back(new Evil(broccoli::GridPoint(x, y), rm.textures.at("agent_evil")));
    }
  }

}

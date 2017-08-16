//
// Created by leo on 7/17/17.
//

#include "game-grid.hpp"
#include "collectible.hpp"
#include "Tree.hpp"

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
    while (y < rows && std::getline(infile, line)) {
      std::istringstream iss(line);
      int tile_nb;
      while ((iss >> tile_nb)) {
        GridTile tile(broccoli::GridPoint(x, y), TileType(tile_nb),
                      &rm.textures.at("base"));
        grid._grid_tiles.push_back(tile);
        x++;
      }
      y++;
      x = 0;
    }
    std::getline(infile, line);
    x = 0, y = 0;
    while (y < rows && std::getline(infile, line)) {
      std::istringstream iss(line);
      unsigned int tile_height;
      while ((iss >> tile_height)) {
        grid._grid_tiles[y * grid._cols + x].set_height(tile_height);
        grid._grid_tiles[y * grid._cols + x].elevate(&rm.textures.at("edge"));
        x++;
      }
      y++;
      x = 0;
    }
    std::getline(infile, line);
    x = 0, y = 0;
    while (y < rows && std::getline(infile, line)) {
      std::istringstream iss(line);
      unsigned int object_id;
      while ((iss >> object_id)) {
        if (object_id == 1) {
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(grid._grid_tiles[y * grid._cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling")));
        }
        else if (object_id == 2) {
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(grid._grid_tiles[y * grid._cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling_snow")));
        }
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
    for (unsigned int y = 0; y < _rows; y++) {
      for (unsigned int x = 0; x < _cols; x++) {
        _grid_tiles[y * _cols + x].draw(target_window, (x != _cols - 1 && y != _rows - 1));
        for (broccoli::GridElement *f : _grid_elements[y * _cols + x]) {
          Drawable *drawable = dynamic_cast<Drawable *>(f);
          if (drawable) {
            drawable->draw(target_window);
          }
        }
      }
    }
  }

  void GameGrid::load_agents(ResourcesManager &rm, broccoli::Context &context) {
    unsigned int x, y;
    for (int i = 0; i < NB_GOOD; i++) {
      x = rand() % _cols;
      y = rand() % _rows;
      if (_grid_tiles[y * _cols + x].get_type() != SEA) {
        sf::Texture &t = rm.textures.at("agent_good");
        Good *e = new Good(broccoli::GridPoint(x, y), &t, *this);
        this->_grid_elements[y * _cols + x].push_back(e);
        addElementAt(e, broccoli::GridPoint(x, y));
        context.add_agent(e);
      }
    }
    for (int i = 0; i < NB_EVIL; i++) {
      x = rand() % _cols;
      y = rand() % _rows;
      if (_grid_tiles[y * _cols + x].get_type() != SEA) {
        sf::Texture &t = rm.textures.at("agent_evil");
        Evil *e = new Evil(broccoli::GridPoint(x, y), &t, *this);
        this->_grid_elements[y * _cols + x].push_back(e);
        addElementAt(e, broccoli::GridPoint(x, y));
        context.add_agent(e);
      }
    }
  }

}

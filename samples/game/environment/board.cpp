//
// Created by leo on 7/17/17.
//

#include "board.hpp"
#include "ressource.hpp"
#include "tree.hpp"
#include "ore.hpp"

#include <fstream>
#include <sstream>
#include <game/agent/peon.hpp>
#include <game/agent/portal.hpp>

namespace game {

  game::Board::Board(unsigned int rows, unsigned int cols, ResourcesManager &rm, broccoli::Context &context)
      : Grid(rows, cols), _rm(rm), _context(context)
  {}

  Board game::Board::load_from_file(const char *file, ResourcesManager &rm, broccoli::Context &context) {
    std::ifstream infile(file);
    std::string line;
    unsigned int cols, rows;
    infile >> cols;
    infile >> rows;
    std::getline(infile, line);
    Board grid(rows, cols, rm, context);
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
        if (object_id == 1 && grid._grid_tiles[y * grid._cols + x].get_type() == GRASS) {
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(grid._grid_tiles[y * grid._cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling"),
              &rm.textures.at("shadow")));
        }
        else if (object_id == 2 && grid._grid_tiles[y * grid._cols + x].get_type() == SNOW) {
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(grid._grid_tiles[y * grid._cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling_snow"),
              &rm.textures.at("shadow")));
        }
        else if (object_id == 3) {
          grid._grid_elements[y * grid._cols + x].push_back(
              new Ore(grid._grid_tiles[y * grid._cols + x], &rm.textures.at("ore"),
                       &rm.textures.at("shadow")));
        }
        else {
          int coin = rand() % 5;
          if (coin == 0) {
            coin = rand() % 3 + 1;
            std::stringstream ss;
            if (grid._grid_tiles[y * grid._cols + x].get_type() == SEA)
              continue;
            switch (grid._grid_tiles[y * grid._cols + x].get_type()) {
              case GRASS:
                ss << "d_grass_";
                break;
              case SAND:
                ss << "d_sand_";
                break;
              case ROCK:
                ss << "d_rock_";
                break;
              case SNOW:
                ss << "d_snow_";
                break;
              case SEA:break;
            }
            ss << coin;
            grid._grid_tiles[y * grid._cols + x].set_decoration(&rm.textures.at(ss.str()));
          }
        }
        x++;
      }
      y++;
      x = 0;
    }
    return grid;
  }

  const game::GridTile &game::Board::get_tile(int x, int y) {
    return _grid_tiles[y * _cols + x];
  }

  void Board::draw(sf::RenderWindow &target_window) {
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

  void Board::load_agents() {
    unsigned int x, y;
    Portal *portal = new Portal(_grid_tiles[6 * _cols + 5], &_rm.textures.at("portal"),
                                &_rm.textures.at("shadow"), *this);
    this->_grid_elements[6 * _cols + 5].push_back(std::move(portal));
    addElementAt(portal, broccoli::GridPoint(5, 6));
    _context.add_agent(portal);
    for (int i = 0; i < NB_GOOD; i++) {
      x = 3;
      y = 4;
      // x = rand() % _cols;
      // y = rand() % _rows;
      if (_grid_tiles[y * _cols + x].get_type() != SEA && !_grid_elements[y * _cols + x].size()) {
        sf::Texture &t = _rm.textures.at("agent_blue");
        Peon *e = new Peon(_grid_tiles[y * _cols + x], &t, &_rm.textures.at("shadow"), *this, portal->get_position());
        this->_grid_elements[y * _cols + x].push_back(std::move(e));
        addElementAt(e, broccoli::GridPoint(x, y));
        _context.add_agent(e);
      }
    }
  }

  void Board::update(float delta) {
    for (unsigned int y = 0; y < _rows; y++) {
      for (unsigned int x = 0; x < _cols; x++) {
        for (broccoli::GridElement *f : _grid_elements[y * _cols + x]) {
          Updatable *updatable = dynamic_cast<Updatable *>(f);
          if (updatable) {
            updatable->update(delta);
          }
        }
      }
    }
  }

}

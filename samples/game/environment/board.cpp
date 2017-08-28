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

namespace game {

  game::Board::Board(unsigned int rows, unsigned int cols) : Grid(rows, cols) {
  }

  Board game::Board::load_from_file(const char *file, ResourcesManager &rm) {
    std::ifstream infile(file);
    std::string line;
    unsigned int cols, rows;
    infile >> cols;
    infile >> rows;
    std::getline(infile, line);
    Board grid(rows, cols);
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
          /*
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(_grid_tiles[y * _cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling"),
              &rm.textures.at("shadow")));
              */
        }
        else if (object_id == 2) {
          /*
          grid._grid_elements[y * grid._cols + x].push_back(
              new Tree(_grid_tiles[y * _cols + x], &rm.textures.at("bracken"), &rm.textures.at("sappling_snow"),
              &rm.textures.at("shadow")));
              */
        }
        else if (object_id == 3) {
          /*
          grid._grid_elements[y * grid._cols + x].push_back(
              new Ore(_grid_tiles[y * _cols + x], &rm.textures.at("ore"),
                       &rm.textures.at("shadow")));
                       */
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

  void Board::load_agents(ResourcesManager &rm, broccoli::Context &context) {
    unsigned int x, y;
    for (int i = 0; i < NB_GOOD; i++) {
      x = rand() % _cols;
      y = rand() % _rows;
      if (_grid_tiles[y * _cols + x].get_type() != SEA && !_grid_elements[y * _cols + x].size()) {
        sf::Texture &t = rm.textures.at("agent_blue");
        Peon *e = new Peon(_grid_tiles[y * _cols + x], &t, &rm.textures.at("shadow"), *this);
        this->_grid_elements[y * _cols + x].push_back(e);
        addElementAt(e, broccoli::GridPoint(x, y));
        context.add_agent(e);
      }
    }
  }

}

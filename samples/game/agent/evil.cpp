//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include "evil.hpp"

namespace game {

  Evil::Evil(broccoli::GridPoint position, sf::Texture &texture, GameGrid &grid)
      : GridElement(position, true), _grid(grid)
  {
    _sprite.setTexture(texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
  }

  Evil::~Evil() {
  }

  void Evil::step() {
    move_normally();
  }

  void Evil::update(float delta) {
  }

  void Evil::move_normally() {
    int offset_x[5] = {-1, 0, 0, 1, 0};
    int offset_y[5] = {0, -1, 1, 0, 0};
    int move = rand() % 5;
    while (_position._x + offset_x[move] >= _grid.get_cols()
           || _position._y + offset_y[move] >= _grid.get_rows()
           || _grid._grid_tiles[(_position._y + offset_y[move]) * _grid.get_cols()
                                + _position._x + offset_x[move]].get_type() == MOUNTAIN
           || _grid._grid_tiles[(_position._y + offset_y[move]) * _grid.get_cols()
                                + _position._x + offset_x[move]].get_type() == WATER)
      move = (move + 1) % 5;
    broccoli::GridPoint new_pos(_position._x + offset_x[move], _position._y + offset_y[move]);
    _grid.moveElementTo(this, _position, new_pos);
  }

}

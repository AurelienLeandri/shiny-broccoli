//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include "good.hpp"

namespace game {

  Good::Good(broccoli::GridPoint position, sf::Texture &texture, GameGrid &grid)
      : GridElement(position), _grid(grid)
  {
    _sprite.setTexture(texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
  }

  Good::~Good() {
  }

  void Good::step() {
  }

  void Good::update(float delta) {
  }

  void Good::move_normally() {
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
    _grid.modify<Good, broccoli::GridPoint>(*this, new_pos, [](Good &elt, broccoli::GridPoint pos) {
      elt._position._x = pos._x;
      elt._position._y = pos._y;
    });
  }

}

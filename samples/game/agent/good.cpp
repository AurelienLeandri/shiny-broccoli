//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "good.hpp"

namespace game {

  Good::Good(broccoli::GridPoint position, const sf::Texture *texture, GameGrid &grid)
      : GridElement(position, true), _grid(grid)
  {
    _elapsed_time = 0;
    _texture = texture;
    _sprite.setTexture(*_texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
    _sprite.setScale(sf::Vector2f(TILE_SIZE / _sprite.getTexture()->getSize().x,
                                  TILE_SIZE / _sprite.getTexture()->getSize().y));
  }

  Good::~Good() {
  }

  int Good::fibo(int n)
  {
    if (n < 2)
      return n;
    return fibo(n - 1) + fibo(n - 2);
  }

  void Good::step() {
    _elapsed_time += _clock.getElapsedTime().asSeconds();
    _clock.restart();
    fibo(30);

      move_normally();
    //  _elapsed_time -= 1;

  }

  void Good::update(float delta) {
    move_normally();
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
    _grid.moveElementTo(this, new_pos);
  }

  Good::Good(const Good &other) : Good(other._position, other.get_texture(), other._grid) {
    this->_position = other._position;
    this->_grid = other._grid;
    this->_sprite = other._sprite;
  }

}

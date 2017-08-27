//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "peon.hpp"

namespace game {

  Peon::Peon(GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, GameGrid &grid)
      : GridElement(tile.get_position(), true), _grid(grid)
  {
    //std::cout << "Positions : x=" << tile._x << ", y=" << tile._y << std::endl;
    _elapsed_time = 0;
    _texture = texture;
    _shadow.setTexture(*shadow_texture);
    _sprite.setTexture(*_texture);
    sf::Vector2f pos = tile.get_middle();

    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 2,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 2));
    _shadow.setColor(sf::Color::Red);

    _sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    _shadow.setPosition(sf::Vector2f(pos.x, pos.y));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.5f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.5f));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 1.2f));
    w = shadow_texture->getSize().x * _shadow.getScale().x;
    h = shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.3f));
  }

  Peon::~Peon() {
  }

  int Peon::fibo(int n)
  {
    if (n < 2)
      return n;
    return fibo(n - 1) + fibo(n - 2);
  }

  void Peon::step() {
    _elapsed_time += _clock.getElapsedTime().asSeconds();
    _clock.restart();
    fibo(30);

      move_normally();
    //  _elapsed_time -= 1;

  }

  void Peon::update(float delta) {
    move_normally();
  }

  void Peon::move_normally() {
    int offset_x[5] = {-1, 0, 0, 1, 0};
    int offset_y[5] = {0, -1, 1, 0, 0};
    int move = rand() % 5;
    while (_position._x + offset_x[move] >= _grid.get_cols()
           || _position._y + offset_y[move] >= _grid.get_rows()
           || _grid._grid_tiles[(_position._y + offset_y[move]) * _grid.get_cols()
                                + _position._x + offset_x[move]].get_type() == SEA)
      move = (move + 1) % 5;
    broccoli::GridPoint new_pos(_position._x + offset_x[move], _position._y + offset_y[move]);
    _grid.moveElementTo(this, new_pos);
  }

  void Peon::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

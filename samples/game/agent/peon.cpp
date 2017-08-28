//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "peon.hpp"

namespace game {

  Peon::Peon(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, Board &grid)
      : Mob(tile, texture, shadow_texture), _grid(grid)
  {
    //std::cout << "Positions : x=" << tile._x << ", y=" << tile._y << std::endl;
    /*
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 0.9f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.3f));
    */
    /*
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 2,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 2));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.5f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.5f));
                                  */

    /*
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 0.9f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 0.9f));
     */
    /*
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
    */
  }

  Peon::~Peon() {
  }

  void Peon::step() {
    //  _elapsed_time -= 1;
  }

  void Peon::update(float delta) {
  }

  void Peon::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

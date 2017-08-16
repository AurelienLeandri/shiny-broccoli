//
// Created by leo on 8/16/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "collectible.hpp"

namespace game {

  game::Collectible::Collectible(const GridTile &tile, const sf::Texture *texture)
      : GridElement(tile.get_position()) {
    _texture = texture;
    _sprite.setTexture(*_texture);
    sf::Vector2f pos = tile.get_middle();
    _sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 4,
                                  TILE_WIDTH / 2 / _sprite.getTexture()->getSize().y / 4));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
  }

  void Collectible::draw(sf::RenderWindow &target_window) {
    target_window.draw(_sprite);
  }

}

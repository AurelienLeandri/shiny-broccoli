//
// Created by leo on 8/16/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "collectible.hpp"

namespace game {

  game::Collectible::Collectible(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture)
      : GridElement(tile.get_position()) {
    _texture = texture;
    _shadow.setTexture(*shadow_texture);
    _sprite.setTexture(*_texture);
  }

  void Collectible::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

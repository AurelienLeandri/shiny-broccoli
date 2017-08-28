//
// Created by leo on 8/27/17.
//

#include <iostream>
#include "board-element.hpp"

namespace game {
  BoardElement::BoardElement(const GridTile &tile, const sf::Texture *sprite_texture,
                             const sf::Texture *shadow_texture)
  : GridElement(tile.get_position()), _shadow_texture(shadow_texture)
  {
    _texture = sprite_texture;
    _sprite.setTexture(*_texture);
    _shadow.setTexture(*_shadow_texture);
  }

  void BoardElement::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  };

}

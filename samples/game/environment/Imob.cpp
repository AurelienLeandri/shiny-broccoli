//
// Created by leo on 8/28/17.
//

#include "Imob.hpp"

namespace game {

  Imob::Imob(const GridTile &tile, const sf::Texture *sprite_texture, const sf::Texture *shadow_texture) : BoardElement(
      tile, sprite_texture, shadow_texture) {
    _pixels_position = tile.get_middle();
    _sprite.setPosition(_pixels_position);
    _shadow.setPosition(_pixels_position);
  }

}
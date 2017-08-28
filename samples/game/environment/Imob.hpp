//
// Created by leo on 8/28/17.
//

#pragma once

#include "board-element.hpp"

namespace game {

  class Imob : public BoardElement {
    public:
      Imob(const GridTile &tile, const sf::Texture *sprite_texture, const sf::Texture *shadow_texture);

  };

}

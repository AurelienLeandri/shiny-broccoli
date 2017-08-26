//
// Created by leo on 8/17/17.
//

#pragma once

#include "collectible.hpp"

namespace game {

  class Ore : public Collectible {
    public:
      Ore(const GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *shadow_texture);
      void draw(sf::RenderWindow &target_window);
  };

}



//
// Created by leo on 8/16/17.
//

#pragma once


#include <context/grid-element.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <game/graphics/drawable.hpp>
#include "grid-tile.hpp"

namespace game {

  class Collectible : public broccoli::GridElement, public Drawable {
    public:
      Collectible(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture);
      void step() {}
      void draw(sf::RenderWindow &target_window);
    protected:
      sf::Sprite _shadow;
  };

}


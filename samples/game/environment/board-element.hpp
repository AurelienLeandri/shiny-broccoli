//
// Created by leo on 8/27/17.
//

#pragma once

#include <context/grid-element.hpp>
#include <SFML/System.hpp>
#include <game/graphics/drawable.hpp>
#include "grid-tile.hpp"

namespace game {

  class BoardElement : public broccoli::GridElement, public Drawable {
    public:
      BoardElement(const GridTile &tile, const sf::Texture *sprite_texture,
                   const sf::Texture *shadow_texture);

    public:
      const sf::Vector2f &get_pixels_position() { return _pixels_position; }
      virtual void draw(sf::RenderWindow &target_window) override;

    protected:
      sf::Vector2f _pixels_position;
      sf::Sprite _shadow;
      const sf::Texture *_shadow_texture;

  };

}

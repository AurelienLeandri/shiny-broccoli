//
// Created by leo on 7/17/17.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../constants.hpp"

namespace game {

  class Drawable {
    public:
      virtual void draw(sf::RenderWindow &target_window) {
        target_window.draw(_sprite);
      };

    protected:
      sf::Sprite _sprite;
      const sf::Texture *_texture;

    public:
      const sf::Sprite &get_sprite() const { return _sprite; }
      void set_sprite_position(float x, float y) { _sprite.setPosition(x, y); }
      const sf::Texture *get_texture() const { return _texture; }
  };

}

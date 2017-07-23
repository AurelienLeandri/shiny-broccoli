//
// Created by leo on 7/17/17.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace game {

  class Drawable {
    public:
      virtual void draw(sf::RenderWindow &target_window) {
        target_window.draw(_sprite);
      };

    protected:
      sf::Sprite _sprite;
  };

}

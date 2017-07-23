//
// Created by leo on 7/17/17.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace game {

  class Drawable {
      virtual void draw(sf::RenderWindow &target_window) = 0;
  };

}

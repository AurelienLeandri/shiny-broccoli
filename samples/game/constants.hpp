//
// Created by leo on 7/23/17.
//

#ifndef SHINYBROCCOLI_CONSTANTS_HPP
#define SHINYBROCCOLI_CONSTANTS_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>

namespace game {
  const float TILE_WIDTH = 128;
  const int NB_EVIL = 0;
  const int NB_GOOD = 1;
  const sf::Color GRASS_COLOR(35, 148, 0, 255);
  const sf::Color SEA_COLOR(1, 107, 162, 255);
  const sf::Color SAND_COLOR(210, 207, 123, 255);
  const sf::Color ROCK_COLOR(79, 78, 33, 255);
  const sf::Color SNOW_COLOR(202, 237, 255, 255);
  const float EDGE_HEIGHT = 16;
}

#endif //SHINYBROCCOLI_CONSTANTS_HPP

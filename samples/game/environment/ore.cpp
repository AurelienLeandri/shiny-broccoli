//
// Created by leo on 8/17/17.
//

#include "ore.hpp"

namespace game {

  game::Ore::Ore(const broccoli::GridPoint &position, const sf::Texture *bracken_texture, const sf::Texture *shadow_texture)
      : Ressource(position, bracken_texture, shadow_texture)
  {}

  void Ore::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

//
// Created by leo on 8/16/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "ressource.hpp"

namespace game {

  game::Ressource::Ressource(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture)
      : Imob(tile, texture, shadow_texture) {
  }

  void Ressource::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

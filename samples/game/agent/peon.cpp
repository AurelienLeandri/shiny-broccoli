//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "peon.hpp"

namespace game {

  Peon::Peon(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, Board &grid)
      : Mob(tile, texture, shadow_texture, grid)
  {}

  Peon::~Peon() {
  }

  void Peon::step() {}

  void Peon::update(float delta) {
  }

  void Peon::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

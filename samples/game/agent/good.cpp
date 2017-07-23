//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include "good.hpp"

namespace game {

  Good::Good(broccoli::GridPoint position, sf::Texture &texture)
      : GridElement(position)
  {
    _sprite.setTexture(texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
  }

  Good::~Good() {
  }

  void Good::step() {
  }

  void Good::update(float delta) {
  }

}

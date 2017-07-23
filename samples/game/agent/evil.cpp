//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include "evil.hpp"

namespace game {

  Evil::Evil(broccoli::GridPoint position, sf::Texture &texture)
      : GridElement(position)
  {
    _sprite.setTexture(texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
  }

  Evil::~Evil() {
  }

  void Evil::step() {
  }

  void Evil::update(float delta) {
  }

}

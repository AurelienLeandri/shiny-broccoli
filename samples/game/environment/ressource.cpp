//
// Created by leo on 8/16/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "ressource.hpp"

namespace game {

  game::Ressource::Ressource(const broccoli::GridPoint &position, const sf::Texture *texture, const sf::Texture *shadow_texture)
      : BoardElement(position, texture, shadow_texture) {
    _texture = texture;
    _shadow.setTexture(*shadow_texture);
    _sprite.setTexture(*_texture);
  }

  void Ressource::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

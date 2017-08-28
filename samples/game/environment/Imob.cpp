//
// Created by leo on 8/28/17.
//

#include "Imob.hpp"

namespace game {

  Imob::Imob(const GridTile &tile, const sf::Texture *sprite_texture, const sf::Texture *shadow_texture) : BoardElement(
      tile, sprite_texture, shadow_texture) {
    float x_offset = -((float) _position._y) * (TILE_WIDTH / 2);
    float y_offset = _position._x * (TILE_WIDTH / 4);
    float x = x_offset + _position._x * (TILE_WIDTH / 2);
    float y = y_offset + _position._y * (TILE_WIDTH / 4);
    _pixels_position.x = x + TILE_WIDTH / 2;
    _pixels_position.y = y + TILE_WIDTH / 4;
    _sprite.setPosition(_pixels_position);
    _shadow.setPosition(_pixels_position);
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 2,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 2));
    _sprite.move(sf::Vector2f(-w / 2.0f, -h * 0.9f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.5f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.5f));
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
  }

}
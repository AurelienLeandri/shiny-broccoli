//
// Created by leo on 8/17/17.
//

#include "ore.hpp"

namespace game {

  game::Ore::Ore(const GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *shadow_texture)
      : Ressource(tile, bracken_texture, shadow_texture)
  {
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 1.25f,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 1.75f));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.75f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.75f));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h * 0.6f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
  }

  void Ore::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

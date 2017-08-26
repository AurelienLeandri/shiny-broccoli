//
// Created by leo on 8/17/17.
//

#include "ore.hpp"

namespace game {

  game::Ore::Ore(const game::GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *shadow_texture)
      : Collectible(tile, bracken_texture, shadow_texture)
  {
    sf::Vector2f pos = tile.get_middle();
    _sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x,
                                  TILE_WIDTH / 2 / _sprite.getTexture()->getSize().y));

    _shadow.setPosition(sf::Vector2f(pos.x, pos.y));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 4,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 4));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
    w = shadow_texture->getSize().x * _shadow.getScale().x;
    h = shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
  }

  void Ore::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

}

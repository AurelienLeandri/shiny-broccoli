//
// Created by leo on 8/17/17.
//

#include "tree.hpp"

namespace game {

  game::Tree::Tree(const game::GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *tree_texture,
    const sf::Texture *shadow_texture)
      : Collectible(tile, bracken_texture, shadow_texture)
  {
    sf::Vector2f pos = tile.get_middle();
    _sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 4,
                                  TILE_WIDTH / 2 / _sprite.getTexture()->getSize().y / 4));

    _shadow.setPosition(sf::Vector2f(pos.x, pos.y));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 2,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 2));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
    w = shadow_texture->getSize().x * _shadow.getScale().x;
    h = shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
    _tree_sprite.setTexture(*tree_texture);
    _tree_sprite.setScale(sf::Vector2f(_sprite.getScale().x, _sprite.getScale().y * 1.5f));
    h = tree_texture->getSize().y * _tree_sprite.getScale().y;
    _tree_sprite.setPosition(sf::Vector2f(pos.x, _sprite.getPosition().y));
    w = tree_texture->getSize().x * _tree_sprite.getScale().x;
    float bracken_h = _texture->getSize().y * _sprite.getScale().y;
    float bracken_w = _texture->getSize().x * _sprite.getScale().x;
    _tree_sprite.move(sf::Vector2f(-w / 2.0f - bracken_w / 19, -h + bracken_h / 4));
  }

  void Tree::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
    target_window.draw(_tree_sprite);
  }

}

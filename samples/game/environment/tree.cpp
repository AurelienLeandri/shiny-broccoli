//
// Created by leo on 8/17/17.
//

#include <iostream>
#include "tree.hpp"

namespace game {

  game::Tree::Tree(const GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *tree_texture,
    const sf::Texture *shadow_texture)
      : Ressource(tile, bracken_texture, shadow_texture)
  {
    std::cout << tile.get_type() << std::endl;
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 3.0f,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 3.0f));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.5f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.5f));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h * 0.7f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));

    _tree_sprite.setTexture(*tree_texture);
    _tree_sprite.setScale(sf::Vector2f(_sprite.getScale().x, _sprite.getScale().y / 1.75f));
    h = tree_texture->getSize().y * _tree_sprite.getScale().y;
    _tree_sprite.setPosition(_pixels_position);
    w = tree_texture->getSize().x * _tree_sprite.getScale().x;
    float bracken_h = _texture->getSize().y * _sprite.getScale().y;
    float bracken_w = _texture->getSize().x * _sprite.getScale().x;
    _tree_sprite.move(sf::Vector2f(-w / 2.0f - bracken_w / 20, -h - bracken_h / 3.5f));
  }

  void Tree::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
    target_window.draw(_tree_sprite);
  }

}

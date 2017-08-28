//
// Created by leo on 8/17/17.
//

#include "tree.hpp"

namespace game {

  game::Tree::Tree(const broccoli::GridPoint &position, const sf::Texture *bracken_texture, const sf::Texture *tree_texture,
    const sf::Texture *shadow_texture)
      : Ressource(position, bracken_texture, shadow_texture)
  {
    _sprite.setScale(sf::Vector2f(_sprite.getScale().x / 2, _sprite.getScale().y / 2));
    /*
    _tree_sprite.setTexture(*tree_texture);
    _tree_sprite.setScale(sf::Vector2f(_sprite.getScale().x, _sprite.getScale().y * 1.5f));
    float h = tree_texture->getSize().y * _tree_sprite.getScale().y;
    _tree_sprite.setPosition(sf::Vector2f(pos.x, _sprite.getPosition().y));
    float w = tree_texture->getSize().x * _tree_sprite.getScale().x;
    float bracken_h = _texture->getSize().y * _sprite.getScale().y;
    float bracken_w = _texture->getSize().x * _sprite.getScale().x;
    _tree_sprite.move(sf::Vector2f(-w / 2.0f - bracken_w / 19, -h + bracken_h / 4));
     */
  }

  void Tree::draw(sf::RenderWindow &target_window) {
    target_window.draw(_shadow);
    target_window.draw(_sprite);
    target_window.draw(_tree_sprite);
  }

}

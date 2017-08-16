//
// Created by leo on 8/17/17.
//

#include "Tree.hpp"

namespace game {

  game::Tree::Tree(const game::GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *tree_texture)
      : Collectible(tile, bracken_texture)
  {
    _tree_sprite.setTexture(*tree_texture);
    sf::Vector2f pos = tile.get_middle();
    _tree_sprite.setScale(_sprite.getScale());
    float h = tree_texture->getSize().y * _tree_sprite.getScale().y;
    _tree_sprite.setPosition(sf::Vector2f(pos.x, _sprite.getPosition().y));
    float w = tree_texture->getSize().x * _tree_sprite.getScale().x;
    float bracken_h = _texture->getSize().y * _sprite.getScale().y;
    float bracken_w = _texture->getSize().x * _sprite.getScale().x;
    _tree_sprite.move(sf::Vector2f(-w / 2.0f - bracken_w / 19, -h + bracken_h / 4));
  }

  void Tree::draw(sf::RenderWindow &target_window) {
      target_window.draw(_sprite);
      target_window.draw(_tree_sprite);
  }

}

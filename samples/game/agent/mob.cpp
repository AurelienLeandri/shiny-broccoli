//
// Created by leo on 8/27/17.
//

#include "mob.hpp"

namespace game {
  Mob::Mob(const GridTile &tile, const sf::Texture *sprite_texture,
      const sf::Texture *shadow_texture, Board &grid)
      : BoardElement(tile, sprite_texture, shadow_texture), _grid(grid) {
    recompute_pixels_position();
  }

  void Mob::move(MoveDirections direction) {
    recompute_pixels_position();
  }

  void Mob::recompute_pixels_position() {
    _pixels_position = _grid._grid_tiles[_position._y * _grid.get_cols() + _position._x].get_middle();
    _sprite.setPosition(_pixels_position);
    _shadow.setPosition(_pixels_position);
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x / 2,
                                  TILE_WIDTH / _sprite.getTexture()->getSize().y / 2));
    _shadow.setScale(sf::Vector2f(TILE_WIDTH / _shadow.getTexture()->getSize().x / 1.5f,
                                  TILE_WIDTH / 2 / _shadow.getTexture()->getSize().y / 1.5f));
    float w = _texture->getSize().x * _sprite.getScale().x;
    float h = _texture->getSize().y * _sprite.getScale().y;
    _sprite.move(sf::Vector2f(-w / 2.0f, -h * 0.9f));
    w = _shadow_texture->getSize().x * _shadow.getScale().x;
    h = _shadow_texture->getSize().y * _shadow.getScale().y;
    _shadow.move(sf::Vector2f(-w / 2.0f, -h / 2.0f));
  }


}

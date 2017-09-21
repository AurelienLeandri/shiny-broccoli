//
// Created by leo on 8/27/17.
//

#include "mob.hpp"
#include "peon.hpp"

namespace game {
  Mob::Mob(const GridTile &tile, const sf::Texture *sprite_texture,
      const sf::Texture *shadow_texture, Board &grid)
      : BoardElement(tile, sprite_texture, shadow_texture, false), _grid(grid) {
    recompute_pixels_position();
  }

  void Mob::move(MoveDirections direction) {
    int new_x = _position._x;
    int new_y = _position._y;
    switch (direction) {
      case UP:
        new_y -= 1;
        break;
      case LEFT:
        new_x -= 1;
        break;
      case DOWN:
        new_y += 1;
        break;
      case RIGHT:
        new_x += 1;
        break;
    }

    if (is_move_valid(new_x, new_y))
      _grid.moveElementTo(this, broccoli::GridPoint((unsigned int) new_x, (unsigned int) new_y));
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

  void Mob::update(float delta) {
    recompute_pixels_position();
  }

  bool Mob::is_move_valid(int pos_x, int pos_y) {
    if (pos_x >= 0 && (unsigned int) pos_x < _grid.get_cols()
        && pos_y >= 0 && (unsigned int) pos_y < _grid.get_rows()
           && _grid._grid_tiles[pos_y * _grid.get_cols() + pos_x].get_type() != SEA) {
      for (auto &e : _grid.get_grid_elements()[pos_y * _grid.get_cols() + pos_x]) {
        Peon *peon = dynamic_cast<Peon *>(e);
        if (!peon)
          return false;
      }
      return true;
    }
    return false;
  }


}

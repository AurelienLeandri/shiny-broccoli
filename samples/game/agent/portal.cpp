//
// Created by leo on 7/26/17.
//

#include "portal.hpp"
#include "peon.hpp"

namespace game {

  Portal::Portal(const game::GridTile &tile, const sf::Texture *sprite_texture, const sf::Texture *shadow_texture,
                 Board &board)
      : Imob(tile, sprite_texture, shadow_texture), _counter(10), _counter_max(10), _board(board)
  {
    _pixels_position = tile.get_middle();
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
    compute_spawn_positions();
    enable_step(true);
  }

  void Portal::step() {
    /* FIXME: create agents
      if (_counter >= _counter_max) {
          _counter -= _counter_max;
        _counter_max *= 2;
        int rand_spawn = (int) (rand() % _spawn_positions.size());
        broccoli::GridPoint position = _spawn_positions[rand_spawn];
        Peon *p = new Peon(_board._grid_tiles[position._y * _board.get_cols() + position._x],
                     &_board.get_resources_manager().textures.at("agent_blue"),
                     &_board.get_resources_manager().textures.at("shadow"), _board);
        _board.addElementAt(p, position);
        _board._context.add_agent(p);
      }
      else
          _counter++;
    */
  }

  void Portal::compute_spawn_positions() {
    for (int i = -1; i <= 1; i++)
      for (int j = -1; j <= 1; j++)
        if (!(j == 0 && i == 0)) {
          int new_x = _position._x + i;
          int new_y = _position._y + j;
          if (!(new_x < 0 || (size_t) new_x >= _board.get_cols() || new_y < 0 || (size_t) new_y >= _board.get_rows()))
            if (_board._grid_tiles[new_y * _board.get_cols()+ new_x].get_type() != SEA)
              _spawn_positions.push_back(broccoli::GridPoint((unsigned int) new_x, (unsigned int) new_y));
        }
  }
}

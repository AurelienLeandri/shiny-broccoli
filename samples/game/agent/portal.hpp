//
// Created by leo on 7/26/17.
//

#pragma once

#include <game/environment/Imob.hpp>
#include <game/environment/board.hpp>

namespace game {

  class Portal : public Imob {
    public:
      Portal(const GridTile &tile, const sf::Texture *sprite_texture,
             const sf::Texture *shadow_texture, Board &board);

    public:
      virtual void step();

    private:
      int _counter;
      int _counter_max;
      Board &_board;
      std::vector<broccoli::GridPoint> _spawn_positions;
      void compute_spawn_positions();
  };

}

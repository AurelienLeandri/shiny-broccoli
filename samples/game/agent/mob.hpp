//
// Created by leo on 8/27/17.
//

#pragma once


#include <context/grid-element.hpp>
#include <game/environment/board-element.hpp>
#include <game/graphics/updatable.hpp>
#include <game/environment/board.hpp>
#include "move-directions.hpp"

namespace game {

  class Mob : public BoardElement, public Updatable {
    public:
      Mob(const GridTile &tile, const sf::Texture *sprite_texture, const sf::Texture *shadow_texture, Board &grid);

    protected:
      virtual void recompute_pixels_position();
      void update(float delta) override;
      bool is_move_valid(int pos_x, int pos_y);

    protected:
      Board &_grid;

    protected:
      void move(MoveDirections direction);
      void move(broccoli::GridPoint position);

  };

}

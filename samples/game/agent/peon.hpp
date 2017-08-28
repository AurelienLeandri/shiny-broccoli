//
// Created by leo on 7/17/17.
//

#pragma once

#include <game/graphics/updatable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>
#include <game/environment/grid-tile.hpp>
#include <game/environment/board.hpp>
#include "mob.hpp"

namespace game {

  class  Peon: public Mob {
    public:
      Peon(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, Board &grid);
      //Peon(const Peon &other) : Peon(other._position, other._texture, other._shadow.getTexture(), other._grid) {}
      virtual ~Peon();

    private:
      Board &_grid;

    public:
      virtual void step() override;
      void update(float delta) override;
      void draw(sf::RenderWindow &target_window) override;
  };

}

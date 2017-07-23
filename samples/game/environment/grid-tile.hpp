//
// Created by leo on 7/17/17.
//

#pragma once

#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>

namespace game {

  enum TileType {
    GRASS = 0,
    FOREST = 1,
    MOUNTAIN = 2,
    WATER = 3
  };

  class GridTile : public broccoli::GridElement, public Drawable {
    public:
      GridTile(const broccoli::GridPoint &position);
      virtual ~GridTile();

    public:
      void draw(sf::RenderWindow &target_window);
      virtual void step() override;

    private:
      sf::Sprite _sprite;

  };

}

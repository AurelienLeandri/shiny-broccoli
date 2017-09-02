//
// Created by leo on 7/17/17.
//

#pragma once

#include <context/grid.hpp>
#include <game/resources-manager.hpp>
#include <context/context.hpp>
#include <game/graphics/updatable.hpp>
#include "grid-tile.hpp"

namespace game {

  class Board : public broccoli::Grid, public Drawable, public Updatable {
    public:
      Board(unsigned int rows, unsigned int cols);

    public:
      virtual void draw(sf::RenderWindow &target_window) override;
      const GridTile &get_tile(int x, int y);
      void load_agents(ResourcesManager &rm, broccoli::Context &context);
      virtual void update(float delta) override;

    public:
      static Board load_from_file(const char *file, ResourcesManager &rm);

    public:
      std::vector<GridTile> _grid_tiles;

  };

}



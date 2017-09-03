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
      Board(unsigned int rows, unsigned int cols, ResourcesManager &rm, broccoli::Context &context);

    public:
      virtual void draw(sf::RenderWindow &target_window) override;
      const GridTile &get_tile(int x, int y);
      void load_agents();
      virtual void update(float delta) override;

    public:
      const ResourcesManager &get_resources_manager() const { return _rm; }
      const broccoli::Context &get_context() const { return _context; }

    public:
      static Board load_from_file(const char *file, ResourcesManager &rm, broccoli::Context &context);

    public:
      std::vector<GridTile> _grid_tiles;
      ResourcesManager &_rm;
      broccoli::Context &_context;

  };

}



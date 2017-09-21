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
#include <set>

namespace game {

  enum PeonState {
    SEARCHING_ORE,
    MINING_ORE,
    RETURNING_ORE,
    FETCHING_ORE
  };

  class  Peon: public Mob {
    public:
      Peon(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, Board &grid,
           broccoli::GridPoint portal_position);
      //Peon(const Peon &other) : Peon(other._position, other._texture, other._shadow.getTexture(), other._grid) {}
      virtual ~Peon();

    public:
      virtual void step() override;
      void draw(sf::RenderWindow &target_window) override;

    private:
      bool compute_path_astar(broccoli::GridPoint pos1, broccoli::GridPoint pos2);
      void reconstruct_path(int current, int start, std::vector<int> came_from);
      int heuristic_cost_estimate(broccoli::GridPoint pos1, broccoli::GridPoint pos2);
      int extract_lowest(std::set<int> &set, std::vector<int> &h_costs);
      const broccoli::GridPoint *search_ore();
      const broccoli::GridPoint *is_ore_present(int pos_x, int pos_y);

    private:
      std::stack<MoveDirections> _path;
      PeonState _state;
      broccoli::GridPoint _portal_position;
  };

}

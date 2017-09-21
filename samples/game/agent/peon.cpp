//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include <set>
#include <game/environment/ore.hpp>
#include "peon.hpp"

namespace game {

  Peon::Peon(const GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, Board &grid,
             broccoli::GridPoint portal_position)
      : Mob(tile, texture, shadow_texture, grid), _portal_position(portal_position), _state(SEARCHING_ORE)
  {}

  Peon::~Peon() {
  }

  void Peon::step() {
    if (_path.size()) {
      move(_path.top());
      _path.pop();
    } else {
      const broccoli::GridPoint *ore_position = nullptr;
      switch (_state) {
        case SEARCHING_ORE:
          // Test if ore is found
          ore_position = search_ore();
          if (ore_position) {
            compute_path_astar(_position, *ore_position);
            std::cout << "state changed to FETCHING_ORE" << std::endl;
            _state = FETCHING_ORE;
          }
          else
            move((MoveDirections) (rand() % 4));
          break;
        case MINING_ORE:
          compute_path_astar(_position, _portal_position);
          std::cout << "state changed to RETURNING_ORE" << std::endl;
          _state = RETURNING_ORE;
          break;
        case RETURNING_ORE:
          if (!_path.size()) {
            std::cout << "state changed to SEARCHING_ORE" << std::endl;
            _state = SEARCHING_ORE;  // FIXME: remember previous ore
          }
          // FIXME Add ore to resources
          // FIXME Test if ore still registered else do search ore
          break;
        case FETCHING_ORE:
          if (!_path.size()) {
            std::cout << "state changed to MINING_ORE" << std::endl;
            _state = MINING_ORE;
          }
          break;
      }
    }
  }

  void Peon::draw(sf::RenderWindow &target_window) {
    recompute_pixels_position();
    target_window.draw(_shadow);
    target_window.draw(_sprite);
  }

  bool Peon::compute_path_astar(broccoli::GridPoint pos1, broccoli::GridPoint pos2) {
    std::set<int> closed_set;
    std::set<int> open_set;
    open_set.insert(pos1._y * _grid.get_cols() + pos1._x);
    std::vector<int> came_from(_grid.get_cols() * _grid.get_rows(), -1);
    std::vector<int> costs(_grid.get_cols() * _grid.get_rows(), -1);
    std::vector<int> h_costs(_grid.get_cols() * _grid.get_rows(), -1);
    costs[pos1._y * _grid.get_cols() + pos1._x] = 0;
    h_costs[pos1._y * _grid.get_cols() + pos1._x] = heuristic_cost_estimate(pos1, pos2);
    int goal_index = pos2._y * _grid.get_cols() + pos2._x;
    int start_index = pos1._y * _grid.get_cols() + pos1._x;
    while (!(open_set.empty())) {
      int current = extract_lowest(open_set, h_costs);
      if (current == goal_index) {
        reconstruct_path(current, start_index, came_from);
        return true;
      }
      closed_set.insert(current);
      for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
          if (i == j || i != 0 && j != 0)
            continue;
          int pos_x = (current % _grid.get_cols() + i);
          int pos_y = (current / _grid.get_cols() + j);
          if (!is_move_valid(pos_x, pos_y))
            continue;
          int neighbor = pos_y * _grid.get_cols() + pos_x;
          if (closed_set.find(neighbor) != closed_set.end())
            continue;
          if (open_set.find(neighbor) == open_set.end())
            open_set.insert(neighbor);
          int candidate_cost = costs[current] + 1;
          if (candidate_cost >= costs[neighbor] && costs[neighbor] != -1)
            continue;
          came_from[neighbor] = current;
          costs[neighbor] = candidate_cost;
          broccoli::GridPoint neighbor_point(neighbor / _grid.get_cols(), neighbor % _grid.get_cols());
          h_costs[neighbor] = costs[neighbor] + heuristic_cost_estimate(neighbor_point, pos2);
        }
    }
    return false;
  }

  // Calculate heuristic for A* using euclidian distance
  int Peon::heuristic_cost_estimate(broccoli::GridPoint pos1, broccoli::GridPoint pos2) {
    return (int) sqrt(pow(pos2._x - pos1._x, 2) + pow(pos2._y - pos2._x, 2));
  }

  int Peon::extract_lowest(std::set<int> &set, std::vector<int> &h_costs) {
    int min = 0;
    int min_index = -1;
    for (auto &e : set) {
      if (h_costs[e] < min) {
        min = h_costs[e];
        min_index = e;
      }
    }
    set.erase(min_index);
    return min_index;
  }

  void Peon::reconstruct_path(int current, int start, std::vector<int> came_from) {
    int prev = 0, prev_x = 0, prev_y = 0, current_x = 0, current_y = 0;
    while (current != start) {
      prev = came_from[current];
      prev_x = prev % _grid.get_cols();
      prev_y = prev / _grid.get_cols();
      current_x = current % _grid.get_cols();
      current_y = current / _grid.get_cols();
      if (prev_x < current_x)
        _path.push(RIGHT);
      else if (prev_x > current_x)
        _path.push(LEFT);
      else if (prev_y < current_y)
        _path.push(DOWN);
      else if (prev_y > current_y)
        _path.push(UP);
      current = prev;
    }
  }

  const broccoli::GridPoint *Peon::search_ore() {
    std::queue<int> indices;
    indices.push(_position._y * _grid.get_cols() + _position._x);
    std::set<int> closed_set;
    while (!indices.empty()) {
      int current = indices.front();
      int current_x = current % _grid.get_cols();
      int current_y = current / _grid.get_cols();
      closed_set.insert(current);
      indices.pop();
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
          if (i == 0 && j == 0 || i != 0 && j != 0)
            continue;
          int pos_x = current_x + i;
          int pos_y = current_y + j;
          int pos = pos_y * _grid.get_cols() + pos_x;
          if (closed_set.find(pos) != closed_set.end())
            continue;
          if (abs(pos_x - _position._x) > 3 || abs(pos_y - _position._y) > 3)
            continue;
          const broccoli::GridPoint *ore_pos = is_ore_present(pos_x, pos_y);
          if (ore_pos)
            return ore_pos;
          indices.push(pos);
        }
    }
    return nullptr;
  }

  const broccoli::GridPoint *Peon::is_ore_present(int pos_x, int pos_y) {
    if (pos_x >= 0 && (unsigned int) pos_x < _grid.get_cols()
        && pos_y >= 0 && (unsigned int) pos_y < _grid.get_rows()
        && _grid._grid_tiles[pos_y * _grid.get_cols() + pos_x].get_type() != SEA) {
      for (auto &e : _grid.get_grid_elements()[pos_y * _grid.get_cols() + pos_x]) {
        Ore *ore = dynamic_cast<Ore *>(e);
        if (ore)
          return &ore->get_position();
      }
    }
    return nullptr;
  }

}

//
// Created by leo on 7/17/17.
//

#include "grid-tile.hpp"

namespace game {

  GridTile::GridTile(const broccoli::GridPoint &position) : GridElement(position) {}

  void GridTile::draw(sf::RenderWindow &target_window) {
    target_window.draw(_sprite);
  }

  GridTile::~GridTile() {
  }

  void GridTile::step() {
  }
}

//
// Created by leo on 7/17/17.
//

#include "grid-tile.hpp"

namespace game {

  GridTile::GridTile(const broccoli::GridPoint &position, TileType type, sf::Texture &texture)
      : GridElement(position), _type(type)
  {
    _sprite.setTexture(texture);
  }

  void GridTile::draw(sf::RenderWindow &target_window) {
    target_window.draw(_sprite);
  }

  GridTile::~GridTile() {
  }

  void GridTile::step() {
  }

  std::string GridTile::getTextureNameForType(TileType type) {
    switch (type) {
      case TileType::GRASS:
        return "tile_grass";
      case TileType::FOREST:
        return "tile_forest";
      case TileType::MOUNTAIN:
        return  "tile_mountain";
      case TileType::WATER:
        return  "tile_water";
      default:
        return "default";
    }
  }
}

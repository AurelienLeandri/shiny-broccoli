//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include "grid-tile.hpp"

namespace game {

  GridTile::GridTile(const broccoli::GridPoint &position, TileType type, const sf::Texture *texture)
      : GridElement(position), _type(type)
  {
    _texture = texture;
    _sprite.setTexture(*_texture);
    _sprite.setPosition(sf::Vector2f(position._x * TILE_SIZE, position._y * TILE_SIZE));
    _sprite.setScale(sf::Vector2f(TILE_SIZE / _sprite.getTexture()->getSize().x,
                                  TILE_SIZE / _sprite.getTexture()->getSize().y));
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
      case TileType::ORE:
        return  "tile_ore";
      case TileType::PORTAL:
        return "tile_portal_good";
      default:
        return "default";
    }
  }

  GridTile::GridTile(const GridTile &other) : GridTile(other._position, other._type, other._texture){
  }
}

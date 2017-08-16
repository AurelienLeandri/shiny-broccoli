//
// Created by leo on 7/17/17.
//

#include <game/constants.hpp>
#include <iostream>
#include "grid-tile.hpp"

namespace game {

  GridTile::GridTile(const broccoli::GridPoint &position, TileType type, const sf::Texture *texture)
      : GridElement(position), _type(type), _height(0)
  {
    _texture = texture;
    _sprite.setTexture(*_texture);
    float x_offset = -((float) position._y) * (TILE_WIDTH / 2);
    float y_offset = position._x * (TILE_WIDTH / 4);
    float x = x_offset + position._x * (TILE_WIDTH / 2);
    float y = y_offset + position._y * (TILE_WIDTH / 4);
    _sprite.setPosition(sf::Vector2f(x, y));
    _sprite.setScale(sf::Vector2f(TILE_WIDTH / _sprite.getTexture()->getSize().x,
                                  TILE_WIDTH / 2 / _sprite.getTexture()->getSize().y));
    _sprite.setColor(get_color_from_type(type));

  }

  void GridTile::elevate(sf::Texture *height_texture) {
    if (height_texture) {
      _edge_sprite.setTexture(*height_texture);
      float w = _edge_sprite.getTexture()->getSize().x;
      float new_scale = TILE_WIDTH / w;
      _edge_sprite.setScale(sf::Vector2f(new_scale, new_scale * 2));
      _edge_sprite.setColor(get_color_from_type(_type));
      _sprite.move(sf::Vector2f(0, -EDGE_HEIGHT * _height));
      _edge_sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, _sprite.getPosition().y + TILE_WIDTH / 4));
    }
    _middle.x = _sprite.getPosition().x + TILE_WIDTH / 2;
    _middle.y = _sprite.getPosition().y + TILE_WIDTH / 4;
  }

  void GridTile::draw(sf::RenderWindow &target_window) {
    target_window.draw(_edge_sprite);
    target_window.draw(_sprite);
    /*
    sf::CircleShape shape(5);
    if (_height == 0)
      shape.setFillColor(sf::Color(0, 255, 0));
    else shape.setFillColor(sf::Color(255, 0, 0));
    shape.setPosition(_middle - sf::Vector2f(2.5, 2.5));
    target_window.draw(shape);
     */
  }

  void GridTile::draw(sf::RenderWindow &target_window, bool draw_edge) {
    if (!draw_edge) {
      sf::RectangleShape shape(sf::Vector2f(TILE_WIDTH, TILE_WIDTH * 2));
      shape.setFillColor(sf::Color::Black);
      shape.setPosition(_edge_sprite.getPosition());
      target_window.draw(shape);
      target_window.draw(_sprite);
    }
    else
      draw(target_window);
  }

  GridTile::~GridTile() {
  }

  void GridTile::step() {
  }

  GridTile::GridTile(const GridTile &other) : GridTile(other._position, other._type, other._texture){
  }

  sf::Color GridTile::get_color_from_type(TileType type) {
    switch (type) {
      case TileType::GRASS:
        return GRASS_COLOR;
      case TileType::SEA:
        return SEA_COLOR;
      case TileType::SAND:
        return SAND_COLOR;
      case TileType::ROCK:
        return ROCK_COLOR;
      case TileType::SNOW:
        return SNOW_COLOR;
      default:
        return GRASS_COLOR;
    }
  }

}

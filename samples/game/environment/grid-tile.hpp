//
// Created by leo on 7/17/17.
//

#pragma once

#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>

namespace game {

  enum TileType {
    GRASS = 0,
    SEA = 1,
    SAND = 2,
    ROCK = 3,
    SNOW = 4,
  };

  class GridTile : public broccoli::GridElement, public Drawable {
    public:
      GridTile(const broccoli::GridPoint &position, TileType type, const sf::Texture *texture);
      GridTile(const GridTile &other);
      virtual ~GridTile();

    public:
      void draw(sf::RenderWindow &target_window);
      virtual void step() override;

    public:
      const TileType &get_type() const { return _type; }
      void set_height(unsigned int height) { _height = height; }
      void elevate(sf::Texture *height_texture);
      const sf::Vector2f get_middle() const { return _middle; };


    private:
      TileType _type;
      unsigned int _height;
      sf::Sprite _edge_sprite;
      sf::Vector2f _middle;

    private:
      static sf::Color get_color_from_type(TileType type);
  };

}

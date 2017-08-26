//
// Created by leo on 8/17/17.
//

#pragma once

#include "collectible.hpp"

namespace game {

  class Tree : public Collectible {
    public:
      Tree(const GridTile &tile, const sf::Texture *bracken_texture, const sf::Texture *tree_texture,
      const sf::Texture *shadow_texture);
      void draw(sf::RenderWindow &target_window);

    private:
      sf::Sprite _tree_sprite;

  };

}



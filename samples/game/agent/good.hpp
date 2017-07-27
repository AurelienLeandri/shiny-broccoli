//
// Created by leo on 7/17/17.
//

#pragma once

#include <game/graphics/updatable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>
#include <game/environment/grid-tile.hpp>
#include <game/environment/game-grid.hpp>

namespace game {

  class  Good: public broccoli::GridElement, public Drawable, public Updatable {
    public:
      Good(broccoli::GridPoint position, const sf::Texture *texture, GameGrid &grid);
      Good(const Good &other);
      virtual ~Good();
      int fibo(int n);

    private:
      void move_normally();

    private:
      GameGrid &_grid;

    public:
      virtual void step() override;
      void update(float delta) override;
  };

}

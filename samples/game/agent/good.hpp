//
// Created by leo on 7/17/17.
//

#pragma once

#include <game/graphics/updatable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>
#include <game/environment/game-grid.hpp>

namespace game {

  class Good : public broccoli::GridElement, public Drawable, public Updatable {
    public:
      Good(broccoli::GridPoint position, sf::Texture &texture, GameGrid &grid);
      virtual ~Good();

    private:
      const GameGrid &_grid;

    public:
      virtual void step() override;
      void update(float delta) override;
      void move_normally();
  };

}

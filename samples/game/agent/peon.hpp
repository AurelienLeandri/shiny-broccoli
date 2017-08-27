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

  class  Peon: public broccoli::GridElement, public Drawable, public Updatable {
    public:
      Peon(GridTile &tile, const sf::Texture *texture, const sf::Texture *shadow_texture, GameGrid &grid);
      //Peon(const Peon &other) : Peon(other._position, other._texture, other._shadow.getTexture(), other._grid) {}
      virtual ~Peon();
      int fibo(int n);

    private:
      void move_normally();

    private:
      GameGrid &_grid;
      sf::Clock _clock;
      float _elapsed_time;
      sf::Sprite _shadow;

    public:
      virtual void step() override;
      void update(float delta) override;
      void draw(sf::RenderWindow &target_window) override;
  };

}

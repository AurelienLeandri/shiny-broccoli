//
// Created by leo on 7/17/17.
//

#pragma once

#include <game/graphics/updatable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <context/grid-element.hpp>
#include <game/graphics/drawable.hpp>

namespace game {

  class  Evil: public broccoli::GridElement, public Drawable, public Updatable {
    public:
      Evil(broccoli::GridPoint position, sf::Texture &texture);
      virtual ~Evil();

    public:
      virtual void step() override;
      void update(float delta) override;
  };

}

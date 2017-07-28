//
// Created by leo on 7/23/17.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <game/environment/game-grid.hpp>
#include <game/graphics/updatable.hpp>
#include <context/context.hpp>
#include "resources-manager.hpp"

namespace game {

  class Game : public Drawable, public Updatable {
    public:
      Game(sf::RenderWindow *render_window, ResourcesManager &rm);
      virtual ~Game();

    public:
      virtual void draw(sf::RenderWindow &target_window) override;
      virtual void update(float delta) override;
      static void *update_key(void *g);
      static void *game_loop(void *g);

    public:
      void start();

    private:
      sf::View _view;
      sf::RenderWindow *_render_window;
      ResourcesManager &_rm;
      GameGrid _grid;
      broccoli::Context context;
      std::mutex _view_mutex;
      float _time_between_steps;
      float _camera_offset_x;
      float _camera_offset_y;
  };

}

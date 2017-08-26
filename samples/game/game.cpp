//
// Created by leo on 7/23/17.
//

#include <iostream>
#include "game.hpp"

namespace game {

  Game::Game(sf::RenderWindow *render_window, ResourcesManager &rm)
      : _view(sf::FloatRect(0, 0, 640, 640)), context(broccoli::ThreadingPolicy::ALL, broccoli::LockPolicy::LOCK_FREE),
        _rm(rm), _grid(game::GameGrid::load_from_file("base.map", _rm))
  {
    _render_window = render_window;
    _render_window->setView(_view);
    _grid.set_data_manager(&context.get_data_manager());
    _grid.load_agents(_rm, context);
    _time_between_steps = 0;
    //context.get_data_manager().poll_requests();
    //context.update();
  }

  Game::~Game() {
  }

  void Game::draw(sf::RenderWindow &target_window) {
    _grid.draw(target_window);
  }

  void Game::update(float delta) {
    sf::Clock update_clock;

    context.update();
    float t =  update_clock.getElapsedTime().asSeconds();

  }

  void Game::start() {
      sf::Event event;
      sf::Clock update_clock;
      sf::Clock render_clock;
      float elapsed_time = 0;
      while (_render_window->isOpen()) {
       while (_render_window->pollEvent(event)) {
              if (event.type == sf::Event::Closed)
                _render_window->close();
              if (event.type == sf::Event::KeyPressed) {
                int offsetx = 0, offsety = 0, val = 15;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                  offsetx = -val;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                  offsetx = val;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                  offsety = -val;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                  offsety = val;
                _camera_offset_x = offsetx;
                _camera_offset_y = offsety;
              }
              else {
                _camera_offset_x = 0;
                _camera_offset_y = 0;
              }
            }
        elapsed_time = update_clock.getElapsedTime().asSeconds();
        update_clock.restart();

        update(elapsed_time);
        _render_window->clear();
        elapsed_time = render_clock.getElapsedTime().asSeconds();
        render_clock.restart();
        _view.move(_camera_offset_x * elapsed_time * 20, _camera_offset_y * elapsed_time * 20);
        _render_window->setView(_view);
        draw(*_render_window);
        _render_window->display();
      }
  }
}

//
// Created by leo on 7/23/17.
//

#include <iostream>
#include "game.hpp"

namespace game {

  Game::Game(sf::RenderWindow *render_window, ResourcesManager &rm)
      : _view(sf::FloatRect(0, 0, 640, 640)), context(broccoli::ThreadingPolicy::NONE),
        _rm(rm), _grid(game::GameGrid::load_from_file("big.map", _rm))
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
    context.update();
  }

  void Game::start() {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, update_key, this);
    pthread_create(&threads[1], NULL, game_loop, this);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_exit(NULL);
  }

  void *Game::update_key(void *a) {
    Game *g = reinterpret_cast<Game*>(a);
    sf::Event event;
    while (g->_render_window->isOpen()) {
      g->_view_mutex.lock();
      while (g->_render_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          g->_render_window->close();
        if (event.type == sf::Event::KeyPressed) {
          int offsetx = 0, offsety = 0, val = 5;
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            offsetx = -val;
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            offsetx = val;
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            offsety = -val;
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            offsety = val;
          g->_camera_offset_x = offsetx;
          g->_camera_offset_y = offsety;
        }
        else {
          g->_camera_offset_x = 0;
          g->_camera_offset_y = 0;
        }
      }
      g->_view_mutex.unlock();
    }
    pthread_exit(NULL);
  }

  void *Game::game_loop(void *a) {
    Game *g = reinterpret_cast<Game*>(a);
    sf::Clock update_clock;
    sf::Clock render_clock;
    float elapsed_time = 0;
    while (g->_render_window->isOpen()) {
      elapsed_time = update_clock.getElapsedTime().asSeconds();
      update_clock.restart();
      g->update(elapsed_time);
      g->_view_mutex.lock();
      g->_render_window->clear();
      elapsed_time = render_clock.getElapsedTime().asSeconds();
      render_clock.restart();
      g->_view.move(g->_camera_offset_x * elapsed_time * 20, g->_camera_offset_y * elapsed_time * 20);
      g->_render_window->setView(g->_view);
      g->draw(*g->_render_window);
      g->_render_window->display();
      g->_view_mutex.unlock();
    }
    pthread_exit(NULL);
  }
}

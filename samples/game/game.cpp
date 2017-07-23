//
// Created by leo on 7/23/17.
//

#include "game.hpp"

namespace game {

  Game::Game(sf::RenderWindow *render_window, ResourcesManager &rm)
      : _rm(rm), _grid(game::GameGrid::load_from_file("base.map", _rm))
  {
    _render_window = render_window;
    _grid.load_agents(_rm);
  }

  Game::~Game() {
  }

  void Game::draw(sf::RenderWindow &target_window) {
    _grid.draw(target_window);
  }

  void Game::update(float delta) {
  }

  void Game::start() {
    sf::Clock clock;
    sf::Event event;
    float elapsed_time = 0;

    while (_render_window->isOpen()) {
      while (_render_window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          _render_window->close();
      }

      elapsed_time = clock.getElapsedTime().asSeconds();
      clock.restart();
      update(elapsed_time);
      clock.restart();

      _render_window->clear();
      draw(*_render_window);
      _render_window->display();
    }
  }
}

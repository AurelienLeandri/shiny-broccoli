#include <game/environment/game-grid.hpp>
#include "game.hpp"

int main() {
  sf::RenderWindow *render_window = new sf::RenderWindow(sf::VideoMode(640, 640), "PRPAgents");
  game::ResourcesManager rm;
  rm.load_textures("textures/");
  game::Game game(render_window, rm);
  game.start();
  delete render_window;
  return 0;
}

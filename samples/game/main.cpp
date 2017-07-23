#include <iostream>
#include <game/environment/game-grid.hpp>

int main() {
  game::ResourcesManager rm;
  rm.load_textures("textures/");
  game::GameGrid gg = game::GameGrid::load_from_file("base.map", rm);
  return 0;
}

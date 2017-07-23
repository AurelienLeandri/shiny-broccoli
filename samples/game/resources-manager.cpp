//
// Created by leo on 7/23/17.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include "resources-manager.hpp"

namespace game {

  void ResourcesManager::load_textures(std::string path) {
    std::ifstream infile(path + "index.txt");
    std::string line;
    std::string file_key, file_path;
    while (std::getline(infile, line)) {
      std::istringstream iss(line);
      iss >> file_key >> file_path;
      sf::Texture texture;
      texture.loadFromFile(path + file_path);
      textures.insert(std::pair<std::string, sf::Texture>(file_key, std::move(texture)));
    }
  }

}

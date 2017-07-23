//
// Created by leo on 7/23/17.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>

namespace game {

  class ResourcesManager {
    public:
      ResourcesManager() {}
      virtual ~ResourcesManager() {}

    public:
      void load_textures(std::string path);

    public:
      std::map<std::string, sf::Texture> textures;
  };

}

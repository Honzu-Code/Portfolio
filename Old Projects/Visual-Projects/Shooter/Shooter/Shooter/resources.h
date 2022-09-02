#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "settings.h"

struct Resources {
    std::unordered_map<std::string, sf::Texture> textures;
    sf::Font font;
    void load() {
        load_texture("bullet", settings::bullet_path_to_texture);
        load_texture("player", settings::player_path_to_texture);
        load_texture("opponent", settings::opponent_path_to_texture);
        load_font(settings::path_to_font);
    }
    void load_texture(std::string name, std::string path) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load " << path << std::endl;
            std::abort();
        }
        textures[name] = texture;
    }
    void load_font(std::string path)
    {
        if (!font.loadFromFile(path))
        {
            std::cerr << "Failed to load " << path << std::endl;
            std::abort();
        }
    }
    sf::Texture const & texture(std::string name) {
        return textures[name];
    }
};

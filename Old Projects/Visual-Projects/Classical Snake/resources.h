#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "settings.h"

using std::unordered_map;
using std::string;
struct Resources
{
	std::unordered_map<string,sf::Texture> textures;
	sf::Font font;
	void load()
	{
		load_texture("map", settings::path_to_map);
		load_texture("player", settings::path_to_player);
		load_texture("food", settings::path_to_food);
		load_font(settings::path_to_font);
	}
	void load_texture(string name,string path)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(path))
		{
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
	sf::Texture const& texture(std::string name) {
		return textures[name];
	}
};


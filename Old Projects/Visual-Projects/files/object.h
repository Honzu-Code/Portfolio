#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Object :public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite object;
	sf::Texture texture_for_object;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Object() = default;
	Object(sf::Vector2f pos,string path_to_texture,int width_object, int height_object);
	sf::Sprite & return_object();
	virtual void move() {};
	virtual void check_collision() {};
};


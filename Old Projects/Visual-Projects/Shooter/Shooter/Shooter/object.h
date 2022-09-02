#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "resources.h"

using std::string;
using std::cout;
using std::endl;

class Object :public sf::Transformable
{
protected:
	sf::Sprite object;
public:
	Object(sf::Vector2f pos, Resources const & res);
	sf::Sprite & return_object();
	virtual void move() {};
	virtual bool check_collision() { return true; };
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


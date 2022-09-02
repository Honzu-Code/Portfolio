#pragma once
#include <SFML/Graphics.hpp>
#include "resources.h"
#include "element.h"

class Food : public sf::Transformable, public sf::Drawable
{
private:
	Element food;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Food() = default;
	Food(Resources& const res, sf::Vector2f position, string name_of_texture);
	Element& return_food();
	void restart_position(sf::Vector2f pos);
};


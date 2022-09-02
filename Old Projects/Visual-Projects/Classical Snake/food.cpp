#include "food.h"


Food::Food(Resources& const res, sf::Vector2f position, string name_of_texture)
{
	this->food = Element(res, position, name_of_texture);
}

Element& Food::return_food()
{
	return this->food;
}

void Food::restart_position(sf::Vector2f pos)
{
	this->food.get_element().setPosition(sf::Vector2f(pos));
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->food);
}
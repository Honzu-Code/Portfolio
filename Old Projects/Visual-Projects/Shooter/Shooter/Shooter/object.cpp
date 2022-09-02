#include "object.h"

Object::Object(sf::Vector2f pos, Resources const & res)
{
	this->object.setPosition(pos);
}

sf::Sprite & Object::return_object()
{
	return this->object;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->object, states);
}
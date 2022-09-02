#include "object.h"

Object::Object(sf::Vector2f pos, string path_to_texture, int width_object, int height_object)
{
	if (!this->texture_for_object.loadFromFile(path_to_texture, sf::IntRect(0, 0, width_object, height_object)))
	{
		cout << "Error texture not found" << endl;
	}
	else
	{
		this->object.setTexture(this->texture_for_object);
		this->object.setPosition(pos);
	}
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
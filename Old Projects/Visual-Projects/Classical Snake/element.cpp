#include "element.h"


Element::Element(Resources& const res,sf::Vector2f position,string name_of_texture)
{
	this->element.setTexture(res.textures.at(name_of_texture));
	this->element.setPosition(position);
}

sf::Sprite& Element::get_element()
{
	return this->element;
}

void Element::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->element);
}

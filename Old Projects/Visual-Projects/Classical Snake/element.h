#pragma once
#include <SFML/Graphics.hpp>
#include "resources.h"
#include "settings.h"

class Element : public sf::Transformable, public sf::Drawable
{
protected:
	sf::Sprite element;
	sf::Texture texture;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Element() = default;
	Element(Resources & const res, sf::Vector2f position,string name_of_texture);
	sf::Sprite& get_element();
};


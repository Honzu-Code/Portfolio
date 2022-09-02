#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Opponent : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite paddle;
	sf::Texture texture_of_opponent;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Opponent();
	sf::Sprite get_opponent_sprite();
	void move(sf::CircleShape & ball);
};


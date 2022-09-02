#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Player : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite paddle;
	sf::Texture texture_of_player;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Player();
	sf::Sprite get_player_sprite();
	void move(char where);
};



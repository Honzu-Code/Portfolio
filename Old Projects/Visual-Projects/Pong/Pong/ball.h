#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "score.h"

using std::cout;
using std::endl;

class Ball : public sf::Drawable, public sf::Transformable
{
private:
	sf::CircleShape ball;
	sf::Texture texture_of_ball;
	int x_direction;
	int y_direction;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Ball();
	sf::CircleShape & get_ball_of_game(); //only for opponent because we don't need to use for player, beacause ball method if_bounces will check
	void move(char what);
	void if_bounces(sf::Sprite player,sf::Sprite opponent,Score &score);
};


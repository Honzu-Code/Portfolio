#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Score : public sf::Drawable, public sf::Transformable
{
private:
	sf::Text text;
	sf::Font font;
	int player_score;
	int opponent_score;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Score();
	void upgrade_score(char who);
};


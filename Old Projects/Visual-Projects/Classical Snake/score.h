#pragma once
#include "resources.h"
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Transformable ,public sf::Drawable
{
private:
	sf::Text text;
	int count_score;
public:
	Score(sf::Vector2f pos, Resources& const res)
	{
		count_score = 0;
		this->text.setFont(res.font);
		this->text.setFillColor(sf::Color::Red);
		this->text.setString("Score: " + std::to_string(count_score));
		this->text.setPosition(pos);
	}
	void increase_score();
	void restart_score();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

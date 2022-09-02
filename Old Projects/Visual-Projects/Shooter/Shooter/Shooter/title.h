#pragma once
#include "resources.h"
#include <SFML/Graphics.hpp>
#include <string>

class Title : sf::Transformable
{
private:
	sf::Text score;
	sf::Text lifes;
	int count_score;
	int count_lifes;
public:
	Title(sf::Vector2f pos,Resources & const res)
	{
		count_score = 0;
		count_lifes = 5;

		this->score.setFont(res.font);
		this->score.setFillColor(sf::Color::Red);
		this->score.setString("Score: " + std::to_string(count_score));
		this->score.setPosition(pos);

		this->lifes.setFont(res.font);
		this->lifes.setFillColor(sf::Color::Red);
		this->lifes.setString("Lifes: " + std::to_string(count_lifes));
		this->lifes.setPosition(pos.x,pos.y+70);
	}
	void increase_score();
	void decrease_lifes();
	void reset_all();
	bool check_lifes();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


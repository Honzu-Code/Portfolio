#include "title.h"
#include <SFML/System/Time.hpp>

void Title::increase_score()
{
	this->count_score += 10;
	this->score.setString("Score: " + std::to_string(count_score));
}

void Title::decrease_lifes()
{
	this->count_lifes--;
	this->lifes.setString("Lifes: " + std::to_string(count_lifes));
}

bool Title::check_lifes()
{
	if (this->count_lifes)
		return true;
	else
		return false;
}

void Title::reset_all()
{
	sf::sleep(sf::milliseconds(2000));
	this->count_score = 0;
	this->count_lifes = 5;
	this->score.setString("Score: " + std::to_string(count_score));
	this->lifes.setString("Lifes: " + std::to_string(count_lifes));
}

void Title::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->score, states);
	target.draw(this->lifes, states);
}
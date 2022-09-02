#include "score.h"


void Score::increase_score()
{
	count_score += 1;
	this->text.setString("Score: " + std::to_string(count_score));
}

void Score::restart_score()
{
	count_score = 0;
	this->text.setString("Score: " + std::to_string(count_score));
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->text, states);
}


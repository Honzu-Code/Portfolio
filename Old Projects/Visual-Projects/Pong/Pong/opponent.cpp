#include "opponent.h"
#include "settings.h"

Opponent::Opponent()
{
	if (!this->texture_of_opponent.loadFromFile(settings::paddle_path_to_texture, sf::IntRect(0, 0, settings::width_paddle, settings::height_paddle)))
	{
		cout << "Error texture not found" << endl;
	}
	else
	{
		this->paddle.setTexture(this->texture_of_opponent);
		this->paddle.setPosition(settings::width-40, 10);
	}
}

void Opponent::move(sf::CircleShape& ball)
{
	if (ball.getPosition().y <= this->paddle.getPosition().y)
		this->paddle.move(0, -(settings::move));
	else if (ball.getPosition().y >= this->paddle.getPosition().y + this->paddle.getTexture()->getSize().y)
		this->paddle.move(0, settings::move);
}

sf::Sprite Opponent::get_opponent_sprite()
{
	return this->paddle;
}

void Opponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->paddle, states);
}
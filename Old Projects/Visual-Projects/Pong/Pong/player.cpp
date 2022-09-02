#include "player.h"
#include "settings.h"

Player::Player()
{
	if (!this->texture_of_player.loadFromFile(settings::paddle_path_to_texture, sf::IntRect(0, 0, settings::width_paddle, settings::height_paddle)))
	{
		cout << "Error texture not found" << endl;
	}
	else
	{
		this->paddle.setTexture(this->texture_of_player);
		this->paddle.setPosition(10, 10);
	}
}

void Player::move(char where)
{
   if (this->paddle.getPosition().y >= settings::move)
	 if(where == 'U')
	   this->paddle.move(0, -(settings::move));
   if(this->paddle.getPosition().y + this->paddle.getTexture()->getSize().y <= settings::height - settings::move)
	 if(where == 'D')
	   this->paddle.move(0, (settings::move));
}

sf::Sprite Player::get_player_sprite()
{
	return this->paddle;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->paddle, states);
}
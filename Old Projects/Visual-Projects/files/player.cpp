#include "player.h"
#include "settings.h"

void Player::move_player(char where)
{
	if (this->return_object().getPosition().x >= settings::move_of_player)
		if (where == 'L')
			this->return_object().move(-(settings::move_of_player),0);
	if (this->return_object().getPosition().x + this->return_object().getTexture()->getSize().x <= settings::width - settings::move_of_player)
		if (where == 'R')
			this->return_object().move(settings::move_of_player, 0);
}

void Player::shoot()
{
	int pos_x_of_player = this->return_object().getPosition().x;
	int size_x_of_player = this->return_object().getTexture()->getSize().x;
	int pos_y_of_player = this->return_object().getPosition().y;
	cout << "Position of player = " << pos_x_of_player << "," << pos_y_of_player << " , size = " << size_x_of_player << endl;
	this->bullets.push_back(Bullet(sf::Vector2f(100, 100), settings::bullet_path_to_texture, 3, 5));
	cout << this->bullets.size() << endl;
}


void Player::move_bullets()
{
	if (this->bullets.size() > 0)
	{
		for (int i = 0; i < this->bullets.size(); i++)
		{
			this->bullets[i].move();
			cout << "this->bullets[i] position = " << this->bullets[i].return_object().getPosition().x << ", " << this->bullets[i].return_object().getPosition().y << endl;
		}
	}
}

vector<Bullet>& Player::return_bullets_for_draw()
{
	return this->bullets;
}
#include "ball.h"
#include "settings.h"

Ball::Ball()
{
	if (!this->texture_of_ball.loadFromFile(settings::ball_path_to_texture, sf::IntRect(0, 0, 30, 30)))
	{
		cout << "Error texture not found" << endl;
	}
	else
	{
		this->ball.setRadius(settings::radius_of_ball);
		this->ball.setTexture(&this->texture_of_ball);
		this->ball.setPosition(50, 200);
		this->x_direction = 10;
		this->y_direction = 10;
	}
}

void Ball::move(char what)
{
	switch (what)
	{
	case 'T':
		this->y_direction = -(this->y_direction);
		break;
	case 'D':
		this->y_direction = -(this->y_direction);
		break;
	case 'L':
		this->x_direction = -(this->x_direction);
		break;
	case 'R':
		this->x_direction = -(this->x_direction);
		break;
	case 'P':
		this->ball.setPosition(50, 200);
		this->x_direction = 10;
		this->y_direction = 10;
		break;
	case 'E':
		this->ball.setPosition(50, 200);
		this->x_direction = 10;
		this->y_direction = 10;
		break;
	default:
		break;
	}
	this->ball.move(this->x_direction, this->y_direction);
}

sf::CircleShape& Ball::get_ball_of_game()
{
	return this->ball;
}

void Ball::if_bounces(sf::Sprite player, sf::Sprite opponent, Score &score)
{
	int ball_x_pos = this->ball.getPosition().x;
	int ball_y_pos = this->ball.getPosition().y;
	int ball_width = this->ball.getTexture()->getSize().x;
	int ball_height = this->ball.getTexture()->getSize().y;

	int player_x_pos = player.getPosition().x;
	int player_y_pos = player.getPosition().y;
	int player_width = player.getTexture()->getSize().x;
	int player_height = player.getTexture()->getSize().y;

	int opponent_x_pos = opponent.getPosition().x;
	int opponent_y_pos = opponent.getPosition().y;
	int opponent_width = opponent.getTexture()->getSize().x;
	int opponent_height = opponent.getTexture()->getSize().y;

	if (ball_y_pos < 10)
		this->move('T');
	if (ball_y_pos > settings::height - 10)
		this->move('D');
	if (ball_y_pos >= player_y_pos - (ball_width / 2) &&
		ball_y_pos <= player_y_pos + player_height + (player_height / 2) &&
		ball_x_pos <= player_x_pos + player_width &&
		ball_x_pos >= player_x_pos + player_width-1)
		this->move('L');
	if ((ball_y_pos >= opponent_y_pos - (ball_height / 2) &&
		ball_y_pos <= opponent_y_pos + opponent_height + (ball_height / 2)) &&
		ball_x_pos + ball_width >= opponent_x_pos &&
		ball_x_pos + ball_width <= opponent_x_pos+1)
		this->move('R');
	if (ball_x_pos > settings::width-settings::move)
		{
			this->move('P');
			score.upgrade_score('P');
		}
	if (ball_x_pos < settings::move)
		{
			this->move('E');
			score.upgrade_score('E');
		}
	else
		this->move('N');
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(ball, states);
}


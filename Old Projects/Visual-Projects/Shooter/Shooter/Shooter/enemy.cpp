#include "enemy.h"
#include "settings.h"


void Enemy::move()
{
	this->object.move(0, settings::move_of_enemy);
}

bool Enemy::check_collision()
{
	int enemy_y_pos = this->object.getPosition().y;
	int enemy_height = this->object.getTexture()->getSize().y;
	if (enemy_y_pos + enemy_height >= settings::height - settings::move_of_enemy)
		return true;
	else
		return false;
}


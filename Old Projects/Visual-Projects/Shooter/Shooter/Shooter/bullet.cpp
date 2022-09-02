#include "bullet.h"
#include "settings.h"

void Bullet::move()
{
	this->return_object().move(0, -(settings::move_of_bullet));
}

bool Bullet::check_collision(Enemy & opponent)
{
	if (this->object.getGlobalBounds().intersects(opponent.return_object().getGlobalBounds()))
		return true;
	else
		return false;
}

bool Bullet::check_collision_with_map()
{
	int bullet_y_pos = this->object.getPosition().y;
	if (bullet_y_pos <= settings::move_of_bullet)
		return true;
	else
		return false;
}
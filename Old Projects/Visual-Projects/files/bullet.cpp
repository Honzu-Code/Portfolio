#include "bullet.h"
#include "settings.h"

void Bullet::move()
{
	this->return_object().move(0, -(settings::move_of_bullet));
}


#pragma once
#include "object.h"
#include "enemy.h"

class Bullet : public Object
{
public:
	Bullet(sf::Vector2f pos, Resources const & res) : Object(pos, res) {
		this->object.setTexture(res.textures.at("bullet"));
	};
	void move();
	bool check_collision_with_map();
	bool check_collision(Enemy & opponent);
};


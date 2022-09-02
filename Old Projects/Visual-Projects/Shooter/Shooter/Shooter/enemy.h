#pragma once
#include "object.h"


class Enemy : public Object
{
public:
	Enemy(sf::Vector2f pos, Resources const& res) : Object(pos, res) 
	{
		this->object.setTexture(res.textures.at("opponent"));
	}
	void move();
	bool check_collision();
};


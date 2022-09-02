#pragma once
#include "object.h"

class Bullet : public Object
{
public:
	Bullet() = default;
	Bullet(sf::Vector2f pos, string path_to_texture, int width_object, int height_object) : Object(pos, path_to_texture, width_object, height_object) {};
	void move();
};


#pragma once
#include "object.h"
#include "bullet.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class Player : public Object
{
private:
	vector<Bullet> bullets;
public:
	Player() = default;
	Player(sf::Vector2f pos, string path_to_texture, int width_object, int height_object) : Object(pos, path_to_texture, width_object, height_object) {};
	void move_player(char where);
	void move_bullets();
	vector<Bullet>& return_bullets_for_draw();
	void shoot();
	void check_collision() {};
};


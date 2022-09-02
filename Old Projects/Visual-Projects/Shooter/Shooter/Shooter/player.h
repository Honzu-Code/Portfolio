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
	Player(sf::Vector2f pos, Resources const & res);
	void move(char where);
	void move_bullets();
	vector<Bullet>& return_bullets_for_draw();
	void shoot(Resources const & res);
	bool check_collision() { return true; };
};


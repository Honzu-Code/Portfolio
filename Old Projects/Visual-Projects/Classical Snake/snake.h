#pragma once
#include "element.h"
#include <vector>

using std::vector;

class Snake : public sf::Transformable, public sf::Drawable
{
private:
	vector<Element> parts_of_body;
	int where_to_move_x;
	int where_to_move_y;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Snake(Resources& const res);
	void move(char where);
	Element& return_head();
	bool collision_myself();
	void restart(Resources& const res);
	void grow_snake(Resources& const res);
};


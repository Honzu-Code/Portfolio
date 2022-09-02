#pragma once
#include "element.h"
#include <vector>
#include "food.h"

using std::vector;

class Map : public sf::Transformable , public sf::Drawable
{
private:
	vector<Element> elements_of_map;
	Food food;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Map(const int * array_of_map,int size_x, int size_y, Resources& const res);
	void generate_food(Resources& const res, sf::Vector2f position);
	Food& return_food();
	char check_collision(Element & snake_head);
};


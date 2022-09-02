#include "map.h"


Map::Map(const int* array_of_map, int size_x, int size_y,Resources & const res)
{
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			if (array_of_map[i * size_x + j] == 1)
			{
				this->elements_of_map.push_back(Element(res,sf::Vector2f(j*60,i*60),"map"));
			}
		}
	}
}

void Map::generate_food(Resources& const res, sf::Vector2f position)
{
	this->food.return_food() = Element(res, position, "food");
}

Food& Map::return_food()
{
	return this->food;
}

char Map::check_collision(Element& snake_head)
{
   for(int i=0; i<this->elements_of_map.size(); i++)
	if (snake_head.get_element().getGlobalBounds().intersects(this->elements_of_map[i].get_element().getGlobalBounds()))
		return 'M';
   if (snake_head.get_element().getGlobalBounds().intersects(this->food.return_food().get_element().getGlobalBounds()))
	    return 'F';
   else
		return 'N';
}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < this->elements_of_map.size(); i++)
		target.draw(this->elements_of_map[i]);
	target.draw(this->food);
}
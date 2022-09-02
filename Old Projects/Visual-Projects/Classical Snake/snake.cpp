#include "snake.h"
#include <iostream>

using std::cout;
using std::endl;

Snake::Snake(Resources& const res)
{
	for (int i = 0; i < 3; i++)
		this->parts_of_body.push_back(Element(res,sf::Vector2f(185-i*60,65),"player"));
	this->where_to_move_x = 60;
	this->where_to_move_y = 0;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < this->parts_of_body.size(); i++)
		target.draw(this->parts_of_body[i]);
}
void Snake::move(char where)
{
	switch (where)
	{
	case 'T':
		if (this->parts_of_body[0].get_element().getPosition().y != this->parts_of_body[1].get_element().getPosition().y + 60)
		{
			this->where_to_move_x = 0;
			this->where_to_move_y = -60;
		}
		break;
	case 'D':
		if (this->parts_of_body[0].get_element().getPosition().y != this->parts_of_body[1].get_element().getPosition().y - 60)
		{
			this->where_to_move_x = 0;
			this->where_to_move_y = 60;
		}
		break;
	case 'L':
		if (this->parts_of_body[0].get_element().getPosition().x != this->parts_of_body[1].get_element().getPosition().x + 60)
		{
			this->where_to_move_x = -60;
			this->where_to_move_y = 0;
		}
		break;
	case 'R':
		if (this->parts_of_body[0].get_element().getPosition().x != this->parts_of_body[1].get_element().getPosition().x - 60)
		{
			this->where_to_move_x = 60;
			this->where_to_move_y = 0;
		}
		break;
	}
	sf::Vector2f old_position = this->parts_of_body[0].get_element().getPosition();
	sf::Vector2f old_position_second = this->parts_of_body[1].get_element().getPosition();
	this->parts_of_body[0].get_element().move(where_to_move_x, where_to_move_y);
	for (int i = 1; i < this->parts_of_body.size(); i++)
	{
		old_position_second = this->parts_of_body[i].get_element().getPosition();
		this->parts_of_body[i].get_element().setPosition(old_position);
		old_position = old_position_second;
	}
}

Element& Snake::return_head()
{
	return this->parts_of_body.front();
}

void Snake::restart(Resources & const res)
{
	this->parts_of_body.clear();
	for (int i = 0; i < 3; i++)
		this->parts_of_body.push_back(Element(res, sf::Vector2f(185 - i * 60, 65), "player"));
	this->where_to_move_x = 60;
	this->where_to_move_y = 0;
}

bool Snake::collision_myself()
{
	for (int i = 1; i < this->parts_of_body.size(); i++)
	{
		if (this->parts_of_body.front().get_element().getGlobalBounds().intersects(this->parts_of_body[i].get_element().getGlobalBounds()))
			return true;
	}
	return false;
}

void Snake::grow_snake(Resources& const res)
{
	int last_element_x = this->parts_of_body.back().get_element().getPosition().x;
	int last_element_y = this->parts_of_body.back().get_element().getPosition().y;
	int before_last_element_x = this->parts_of_body[this->parts_of_body.size() - 2].get_element().getPosition().x;
	int before_last_element_y = this->parts_of_body[this->parts_of_body.size() - 2].get_element().getPosition().y;

	if (last_element_x < before_last_element_x)
	{
		this->parts_of_body.push_back(Element(res, sf::Vector2f(last_element_x - 65,last_element_y), "player"));
	}
	else if (last_element_x > before_last_element_x)
	{
		this->parts_of_body.push_back(Element(res, sf::Vector2f(last_element_x + 65, last_element_y), "player"));
	}
	else if (last_element_y < before_last_element_y)
	{
		this->parts_of_body.push_back(Element(res, sf::Vector2f(last_element_y - 65, last_element_y), "player"));
	}
	else if (last_element_y > before_last_element_y)
	{
		this->parts_of_body.push_back(Element(res, sf::Vector2f(last_element_y + 65, last_element_y), "player"));
	}

}
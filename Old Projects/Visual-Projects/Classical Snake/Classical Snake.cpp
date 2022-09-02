#include <SFML/Graphics.hpp>
#include "map.h"
#include "snake.h"
#include <Windows.h>
#include "score.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using std::cout;
using std::endl;

int main()
{
    sf::RenderWindow window(sf::VideoMode(settings::width, settings::height), "Classical Snake");
    const int Array[576] =
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    Resources res;
    res.load();
    Map map(Array,32,18,res);
    Snake snake(res);
    Score score(sf::Vector2f(settings::width - 250, 100), res);
    srand(time(NULL));
    map.generate_food(res, sf::Vector2f(rand() % (settings::width - 180) + 60, rand() % (settings::height - 180) + 60));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    snake.move('T');
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    snake.move('D');
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    snake.move('L');
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    snake.move('R');
                }
            }
        }

        if (map.check_collision(snake.return_head()) == 'M' or snake.collision_myself())
        {
            snake.restart(res);
            score.restart_score();
        }
        if (map.check_collision(snake.return_head()) == 'F')
        {
            map.return_food().restart_position(sf::Vector2f(rand() % (settings::width - 180) + 60, rand() % (settings::height - 180) + 60));
            score.increase_score();
            snake.grow_snake(res);
        }
        snake.move('N');
        window.clear();
        window.draw(score);
        window.draw(map);
        window.draw(snake);
        window.display();
        Sleep(100);
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "opponent.h"
#include "ball.h"
#include "score.h"
#include "settings.h"

int main()
{
    sf::ContextSettings antialiasing;
    antialiasing.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(settings::width, settings::height), "Pong",sf::Style::Default,antialiasing);
 
    Player player;
    Opponent opponent;
    Ball ball;
    Score score;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player.move('U');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                player.move('D');
            }
        }
        opponent.move(ball.get_ball_of_game());
        ball.if_bounces(player.get_player_sprite(),opponent.get_opponent_sprite(),score);
        window.clear(sf::Color(32,117,86));
        window.draw(player);
        window.draw(opponent);
        window.draw(ball);
        window.draw(score);
        window.display();
        sf::sleep(sf::milliseconds(20));
    }

    return 0;
}

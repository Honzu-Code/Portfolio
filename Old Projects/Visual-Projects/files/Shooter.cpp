#include <SFML/Graphics.hpp>
#include "player.h"
#include "settings.h"
#include <Windows.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(settings::width, settings::height), "Shooter");
    Player player(sf::Vector2f(10, 500), settings::player_path_to_texture, 60, 60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                player.move_player('L');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                player.move_player('R');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                player.shoot();
                cout << "here iam " << endl;
            }
        }
        player.move_bullets();
        for (int i = 0; i < player.return_bullets_for_draw().size(); i++)
        {
            window.draw(player.return_bullets_for_draw()[i]);
        }
        window.clear();
        window.draw(player);
        window.display();
        Sleep(20);
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include "player.h"
#include "settings.h"
#include "resources.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include "title.h"

void generete_enemy_on_map(vector<Enemy>& enemy, Resources const& res, int& time);
void check_collision_enemy_and_bullets(vector<Enemy>& enemy, vector<Bullet>& bullets,Title & score);
bool left_key = false;
bool right_key = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(settings::width, settings::height), "Shooter");
    window.setKeyRepeatEnabled(false);
    Resources res;
    res.load();
    Player player(sf::Vector2f(10, settings::height-60), res);
    vector<Enemy> enemies;
    Title score(sf::Vector2f(settings::width-300,10),res);
    srand(time(NULL));
    int time_to_generate_enemy = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    left_key = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    right_key = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    player.shoot(res);
                    //cout << "here iam " << endl;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Left) {
                    left_key = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    right_key = false;
                }
            }
        }
        if(left_key)
            player.move('L');
        if (right_key)
            player.move('R');

        player.move_bullets();    
        for (int i = 0; i < enemies.size(); i++)
            enemies[i].move();
        generete_enemy_on_map(enemies, res, time_to_generate_enemy);
        check_collision_enemy_and_bullets(enemies, player.return_bullets_for_draw(),score);
        if (!score.check_lifes())
        {
            score.reset_all();
            enemies.clear();
        }
        //cout << "time = " << time_to_generate_enemy << endl;
        //cout << "enemies = " << enemies.size() << endl;
        //cout << "bullets = " << player.return_bullets_for_draw().size() << endl;
        window.clear();
        for (int i=0; i< player.return_bullets_for_draw().size(); i++)
            player.return_bullets_for_draw()[i].draw(window, sf::RenderStates());
        for (int i = 0; i < enemies.size(); i++)
            enemies[i].draw(window, sf::RenderStates());
        player.draw(window, sf::RenderStates());
        score.draw(window, sf::RenderStates());
        window.display();
        sf::sleep(sf::milliseconds(20));
        time_to_generate_enemy += 20;
    }

    return 0;
}

void generete_enemy_on_map(vector<Enemy>& enemy, Resources const& res, int& time)
{

    if (time % 800 == 0)
    {
        //cout << "time in function = " << time << endl;
        enemy.push_back(Enemy(sf::Vector2f(rand() % (settings::width - 60), 0), res));
        time = 0;
    }
}

void check_collision_enemy_and_bullets(vector<Enemy>& enemy, vector<Bullet>& bullets,Title & score)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < enemy.size(); j++)
        {
            //cout << "i = " << i <<  endl;
            //cout << "j = " << j << endl;
                if (bullets[i].check_collision(enemy[j]))
                {
                    //cout << "Bullets with enemy = true" << endl;
                    bullets.erase(bullets.begin() + i);
                    //cout << "after delete bullets" << endl;
                    enemy.erase(enemy.begin() + j);
                    //cout << "after delete enemy" << endl;
                    score.increase_score();
                    break;
                }
                     
        }
        //cout << "here iam end of loop for" << endl;
    }
    for (int i=0; i<bullets.size(); i++)
        if (bullets[i].check_collision_with_map())
        {
            //cout << "Bullets with map = true" << endl;
            bullets.erase(bullets.begin() + i);
            //cout << "After with map = true" << endl;
        }
    for (int j = 0; j < enemy.size(); j++)
        if (enemy[j].check_collision())
        {
            enemy.erase(enemy.begin() + j);
            score.decrease_lifes();
        }
}
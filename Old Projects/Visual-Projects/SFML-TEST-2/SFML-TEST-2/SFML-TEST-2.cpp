#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    sf::Texture texture;
    if (!texture.loadFromFile("images/texture.png"))
    {
        cout << "Can't load texture from file" << endl;
    }
    sf::Font font;
    if (!font.loadFromFile("fonts/Subtle Curves Italic.ttf"))
    {
        // error...
    }
    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    text.setPosition(sf::Vector2f(window.getSize().x-200, 0.f));
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 300, 300));
    sprite.setColor(sf::Color(0, 0, 255));
    sprite.setPosition(sf::Vector2f(10.f, 50.f));
    sprite.setOrigin(sf::Vector2f(25.f, 25.f));
    sprite.setRotation(30.f);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setTexture(&texture);
    sf::CircleShape decemagon(80.f, 10);
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(10.f, 10.f)),
        sf::Vertex(sf::Vector2f(150.f, 150.f))
    };
    vector<sf::Vertex> vertices;
    vertices.push_back(sf::Vertex(sf::Vector2f(10.f,10.f),sf::Color::Red));
    vertices.push_back(sf::Vertex(sf::Vector2f(10.f, 100.f), sf::Color::Blue));
    vertices.push_back(sf::Vertex(sf::Vector2f(100.f, 100.f), sf::Color::Green));
    vertices.push_back(sf::Vertex(sf::Vector2f(100.f, 10.f), sf::Color::Yellow));
    vertices.push_back(sf::Vertex(sf::Vector2f(10.f, 10.f), sf::Color::Magenta));
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        for (int i = 0; i < 10; i++)
        {
            sprite.move(sf::Vector2f(1.f, 1.f));
            sprite.rotate(5.f);
            Sleep(30);
        }
        window.draw(sprite);
        window.draw(text);
        window.draw(shape);
        window.draw(decemagon);
        window.draw(line,2,sf::Lines);
        window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
        window.display();
    }

    return 0;
}
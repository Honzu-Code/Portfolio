#pragma once
#include "score.h"
#include <string>
#include "settings.h"

Score::Score()
{
    if (!this->font.loadFromFile(settings::score_path_to_font))
    {
        cout << "Font doesn't load" << endl;
    }
    else
    {
        this->player_score = 0;
        this->opponent_score = 0;
        this->text.setFont(this->font);
        this->text.setString("0:0");
        this->text.setFillColor(sf::Color::Red);
        this->text.setPosition((settings::width/2) - this->text.getLocalBounds().width/2 , 30);
    }
}

void Score::upgrade_score(char what)
{
    what == 'P' ? this->player_score++ : this->opponent_score++;
    this->text.setString(std::to_string(this->player_score) + ":" + std::to_string(this->opponent_score));
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(this->text, states);
}
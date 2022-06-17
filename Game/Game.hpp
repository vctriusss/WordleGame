#pragma once

#include "Cell.hpp"

#define Grid std::vector<std::vector<Cell>>
#define Table std::vector<std::vector<std::string>>

class Game {
public:

    Grid cells;
    Table words;
    int pos;
    int attempt;

    Game();

    void run(sf::RenderWindow &window);

    void paintCells(const std::string &entered, const std::string &correct);

    bool displayError(const std::string &entered);

    void eraseSymbol();


private:

    bool running;
    std::string word;
    sf::Text bottom_text;
    sf::Text right_answer_text;
    sf::Text restart_text;
    sf::Font font;

    void clear();

    void initCells();

    void initTextBoxes();

    void drawObjects(sf::RenderWindow &window);

    void showTextBox(sf::Text &textBox, std::string new_text, const sf::Color &new_color);

    void getInput(const unsigned int &letter);

    void restart(sf::RenderWindow &window);

    void EndGameScenario(bool correct);

};
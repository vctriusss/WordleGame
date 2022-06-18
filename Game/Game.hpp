#pragma once

#include "Cell.hpp"

#define Grid std::vector<std::vector<Cell>>
#define Table std::vector<std::vector<std::string>>

/**
 * @class Game is a class, which is basically a game engine and containts basic methods and parameters of a game
 * */
class Game {
public:

    Grid cells; //< Grid of cells (main visible objects)
    Table words; //< Table of letters
    int pos; //< position of a "cursor"
    int attempt; //< number of current attempt (guess)

    Game();

    void run(sf::RenderWindow &window);

    void paintCells(const std::string &entered, const std::string &correct);

    bool displayError(const std::string &entered);

    void eraseSymbol();


private:

    bool running; //< Shows whether game is running or not (needs for restarting)
    std::string word; //< Correct word
    sf::Text bottom_text; //< Textbox to show errors and result of a game
    sf::Text right_answer_text; //< Textbox to show right answer
    sf::Text restart_text; //< Textbox to show restart text
    sf::Font font; //< Font of a game

    void clear();

    void initCells();

    void initTextBoxes();

    void drawObjects(sf::RenderWindow &window);

    void showTextBox(sf::Text &textBox, std::string new_text, const sf::Color &new_color);

    void getInput(const unsigned int &letter);

    void restart(sf::RenderWindow &window);

    void EndGameScenario(bool correct);

};
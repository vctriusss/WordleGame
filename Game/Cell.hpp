#pragma once

#include <SFML/Graphics.hpp>

/**
 * @struct Cell is a structure, which contains a box (square with outline frame) and a letter
 * @param rect Rectangle which forms a cell body
 * @param letter Letter in a box
 * */
struct Cell {
    sf::RectangleShape rect;
    sf::Text letter;

    Cell();

    Cell(int x, int y, const sf::Font &font, const std::string text);

    void draw(sf::RenderWindow &window);

    void paint(const sf::Color &color, int thickness = 3);

    void setLetter(std::string text = "");

};
#pragma once

#include <SFML/Graphics.hpp>

struct Cell {
    sf::RectangleShape rect;
    sf::Text letter;

    Cell();

    Cell(int x, int y, const sf::Font &font);

    void draw(sf::RenderWindow &window);

    void paint(const sf::Color &color, int thickness = 3);

    void setLetter(std::string text = "");

};
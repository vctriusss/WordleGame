#pragma once
#include <SFML/Graphics.hpp>

struct Cell {
    sf::RectangleShape rect;
    sf::Text letter;
    void draw(sf::RenderWindow &window);
    void paint(sf::Color color, int thickness = 3);
    void text(std::string text = "");
    Cell();
    Cell(int x, int y, sf::Font &font);
};
#pragma once

#include <SFML/Graphics.hpp>

struct Cell {
    sf::RectangleShape rect;
    sf::Text letter;

    void render(sf::RenderWindow &window);

    void paint(const sf::Color &color, int thickness = 3);

    void text(std::string text = "");

    Cell();

    Cell(int x, int y, const sf::Font &font);
};
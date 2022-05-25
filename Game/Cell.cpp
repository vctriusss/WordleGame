#include "Cell.hpp"
#include "constants.hpp"

void Cell::render(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(letter);
}

void Cell::paint(sf::Color color, int thickness) {
    rect.setFillColor(color);
    rect.setOutlineColor(GRAY);
    rect.setOutlineThickness(thickness);
}

Cell::Cell() {}

Cell::Cell(int x, int y, sf::Font &font) {
    rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    rect.setPosition(sf::Vector2f(x, y));
    paint(BLACK);
    int lx = x + WIDTH / 2 - 20;
    int ly = y + HEIGHT / 2 - 50;
    letter = sf::Text("", font, 70);
    letter.setPosition(sf::Vector2f(lx, ly));
    letter.setFillColor(WHITE);
}

void Cell::text(std::string text) {
    letter.setString(text);
}


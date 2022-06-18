#include "Cell.hpp"
#include "constants.hpp"

Cell::Cell() {}

Cell::Cell(int x, int y, const sf::Font &font, const std::string text) {
    rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    rect.setPosition(sf::Vector2f(x, y));
    paint(BLACK);
    int lx = x + WIDTH / 2 - 20;
    int ly = y + HEIGHT / 2 - 50;
    letter = sf::Text(text, font, 70);
    letter.setPosition(sf::Vector2f(lx, ly));
    letter.setFillColor(WHITE);
}

/**
 * Method Cell::draw renders a cell in a window
 * @param window A window to render on
 * */
void Cell::draw(sf::RenderWindow &window) {
    window.draw(rect);
    window.draw(letter);
}

/**
 * Method Cell::paint paints a body of a cell with a given color
 * @param color Color to paint in
 * @param thickness Unnecessary parameter to set the outline thickness of a cell
 * */
void Cell::paint(const sf::Color &color, const int thickness) {
    rect.setFillColor(color);
    rect.setOutlineColor(GRAY);
    rect.setOutlineThickness(thickness);
}

/**
 * Method Cell::setLetter sets a letter of a Cell
 * @param text Letter to set. If not given sets an empty letter
 * */
void Cell::setLetter(std::string text) {
    letter.setString(text);
}

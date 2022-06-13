#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "constants.hpp"

std::string createWord();

sf::Text createTextBox(const std::string &text, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y);

void showText (sf::Text &text, std::string new_text, const sf::Color &new_color);

bool isEnglish(const unsigned int &code);
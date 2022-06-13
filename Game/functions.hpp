#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "constants.hpp"

auto createWord() -> std::string;

auto createTextBox(const std::string &text, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y) -> sf::Text;

auto isEnglish(const unsigned int &code) -> bool;
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "constants.hpp"
#include "Cell.hpp"
#include <vector>

#define Grid std::vector<std::vector<Cell>>
#define Table std::vector<std::vector<std::string>>


auto createWord() -> std::string;

auto createTextBox(const std::string &text, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y) -> sf::Text;

auto isEnglish(const unsigned int &code) -> bool;
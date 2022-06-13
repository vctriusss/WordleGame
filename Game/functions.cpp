#include "functions.hpp"

auto createWord() -> std::string {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int t = rng() % WORDLIST.size();
    auto it = WORDLIST.begin();
    for (int k = 0; k < t; ++k) it++;
    return *it;
}

auto createTextBox(const std::string &text, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y) -> sf::Text {
    auto textBox = sf::Text(text, font, size);
    textBox.setPosition(sf::Vector2f(x, y));
    textBox.setFillColor(textcolor);
    return textBox;
}

auto isEnglish(const unsigned int &code) -> bool {
    return 65 <= code && code <= 90 || 97 <= code && code <= 122;
}
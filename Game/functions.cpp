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

auto showText (sf::Text &text, std::string new_text = "", const sf::Color &new_color = WHITE) -> void {
    if (new_text.empty())
        new_text = text.getString();
    int len = new_text.size();
    sf::Vector2f position = text.getPosition();
    text.setPosition(WIN_WIDTH / 2 - (text.getCharacterSize() / 3 - 1) * len, position.y);
    text.setString(new_text);
    text.setFillColor(new_color);
}

auto isEnglish(const unsigned int &code) -> bool {
    return 65 <= code && code <= 90 || 97 <= code && code <= 122;
}
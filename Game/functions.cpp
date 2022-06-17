#include "functions.hpp"

/**
 * createWord functions is analog of choice() in python
 * @return Function returns random word from a wordlist
*/
auto createWord() -> std::string {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int t = rng() % WORDLIST.size();
    auto it = WORDLIST.begin();
    for (int k = 0; k < t; ++k) it++;
    return *it;
}

/**
 * createTextBox creates a textbox with given parameters
 * @param text Text in the textbox
 * @param font Font of text
 * @param size Text character size
 * @param textcolor Color of a text
 * @param x x coord of a box
 * @param y y coord of a box
 *
 * @return Function returns sf::Text object, which is basically a textbox
 *
 */
auto createTextBox(const std::string &text, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y) -> sf::Text {
    auto textBox = sf::Text(text, font, size);
    textBox.setPosition(sf::Vector2f(x, y));
    textBox.setFillColor(textcolor);
    return textBox;
}

/**
 * isEnglish func checks whether the entered letter is in english alphabet or not
 * @param code Unicode of entered letter
 * @return Function returns bool if letter is English or not*/
auto isEnglish(const unsigned int &code) -> bool {
    return 65 <= code && code <= 90 || 97 <= code && code <= 122;
}
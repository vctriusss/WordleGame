#include "constants.hpp"
#include "Cell.hpp"
#include <chrono>
#include <iostream>
#include <random>

#define Grid std::vector<std::vector<Cell>>
#define Table std::vector<std::vector<std::string>>

int attempt = 0, pos = 0;

auto createWord() -> std::string {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int t = rng() % WORDLIST.size();
    auto it = WORDLIST.begin();
    for (int k = 0; k < t; ++k) it++;
    return *it;
}

auto drawCells(Grid &grid, sf::RenderWindow &window) -> void {
    for (auto &v: grid) {
        for (auto &c: v) {
            c.render(window);
        }
    }
}

auto createText(const std::string &string, const sf::Font &font, int size, const sf::Color &textcolor, int x, int y) -> sf::Text {
    auto text = sf::Text(string, font, size);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(textcolor);
    return text;
}

auto initializeCells(Grid &cells, sf::Font &font) -> void {
    for (int i = 0; i < WORDS_NUMBER; ++i) {
        for (int j = 0; j < LETTERS_NUMBER; ++j) {
            int rec_x = 70 + (WIDTH + 10) * j;
            int rec_y = 50 + (HEIGHT + 20) * i;
            auto cell = Cell(rec_x, rec_y, font);
            cells[i][j] = std::move(cell);
        }
    }
}

auto getInput(Grid &cells, Table &words, const unsigned int &letter) -> void {
    char letter_char = static_cast<char> (letter);
    words[attempt][pos] = std::string(1, letter_char);
    cells[attempt][pos].text(std::string(1, toupper(letter_char)));
}

auto paintCells(Grid &cells, const std::string &entered, const std::string &correct) -> void {
    for (int j = 0; j < LETTERS_NUMBER; ++j) {
        char letter = entered[j];
        if (correct.find(letter) == std::string::npos) {
            cells[attempt][j].paint(GRAY, 0);
            continue;
        }
        bool correct_place = correct.find(letter) == entered.find(letter) ||
                             correct.find(letter) == entered.rfind(letter);
        cells[attempt][j].paint(correct_place ? GREEN : YELLOW, 0);
    }
}

auto showText (sf::Text &text, std::string new_text = "", const sf::Color &new_color = WHITE) -> void {
    if (new_text == "")
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

auto eraseSymbol(Grid &cells, Table &words) -> void {
    words[attempt][pos - 1].clear();
    cells[attempt][pos - 1].text("");
    --pos;
}

int main() {
    sf::Font font;
    Table words(WORDS_NUMBER, std::vector<std::string>(LETTERS_NUMBER, std::string()));
    Grid cells(WORDS_NUMBER, std::vector<Cell>(LETTERS_NUMBER));
    font.loadFromFile("../Fonts/Sono-Medium.ttf");

    auto word = createWord();
    auto bottom_text = createText("", font, 40, BLACK, WIN_WIDTH / 2, WIN_HEIGHT - 250);
    auto right_answer_text = createText(RIGHT_ANSWER + word, font, 40, BLACK,  WIN_WIDTH / 2, WIN_HEIGHT - 175);
    auto restart_text = createText(PRESS_TO_RESTART, font, 40, BLACK, WIN_WIDTH / 2, WIN_HEIGHT- 100);

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Wordle");
    window.setKeyRepeatEnabled(false);

    initializeCells(cells, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed: {
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;

                        case sf::Keyboard::LControl:
                            std::cout << "HINT: " << word;
                            break;

                        case sf::Keyboard::Enter: {
                            bottom_text.setFillColor(BLACK);
                            auto entered = std::string();
                            for (const auto &l: words[attempt])
                                entered += l;

                            if (pos != LETTERS_NUMBER) {
                                showText(bottom_text, NOT_ENOUGH);
                                break;
                            }
                            if (!WORDLIST.contains(entered)) {
                                showText(bottom_text, NOT_IN_WORDLIST);
                                break;
                            }
                            paintCells(cells, entered, word);
                            ++attempt;
                            pos = 0;
                            bool correct = (entered == word);
                            if (correct) {
                                showText(bottom_text, "YOU WIN!", GREEN);
                                showText(restart_text);
                            }

                            if (!correct && attempt == WORDS_NUMBER) {
                                showText(bottom_text, "YOU LOST!", RED);
                                showText(right_answer_text);
                                showText(restart_text);
                            }
                            break;
                        }
                        case sf::Keyboard::BackSpace: {
                            bottom_text.setFillColor(BLACK);
                            if (pos > 0) eraseSymbol(cells, words);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }

                case sf::Event::TextEntered: {
                    auto unicode = event.text.unicode;
                    if (!isEnglish(unicode) || pos >= LETTERS_NUMBER) break;
                    getInput(cells, words, unicode);
                    ++pos;
                }
                default:
                    break;
            }
        }
        window.clear(BLACK);
        drawCells(cells, window);
        window.draw(bottom_text);
        window.draw(restart_text);
        window.draw(right_answer_text);
        window.display();
    }
}

/*
 what can be tested:
  - entering text(creating sf::Event::TextEntered and check if input is get)
  - painting cells (depending on entered word)

*/
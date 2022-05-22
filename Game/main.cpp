#include "constants.hpp"
#include "Cell.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <cctype>

#define Table std::vector<std::vector<Cell>>

int attempt = 0, pos = 0;
bool show_correct = false;
sf::Font font;
std::vector<std::vector<std::string>> words(WORDS_NUMBER, std::vector<std::string>(LETTERS_NUMBER, std::string()));
Table cells(WORDS_NUMBER, std::vector<Cell>(LETTERS_NUMBER));


auto createWord() -> std::string {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int t = rng() % WORDLIST.size();
    auto it = WORDLIST.begin();
    for (int k = 0; k < t; ++k) it++;
    return *it;
}

auto drawCells(Table &table, sf::RenderWindow &window) -> void {
//    window.clear();
    for (auto &v: table) {
        for (auto &c: v) {
            c.draw(window);
        }
    }
//    window.display();
}

auto createText(const std::string &string, int size, sf::Color color, int x, int y) -> sf::Text {
    auto text = sf::Text(string, font, size);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(color);
    return text;
}

auto initializeCells() -> void {
    for (int i = 0; i < WORDS_NUMBER; ++i) {
        for (int j = 0; j < LETTERS_NUMBER; ++j) {
            int rec_x = 70 + (WIDTH + 10) * j;
            int rec_y = 50 + (HEIGHT + 20) * i;
            auto cell = Cell(rec_x, rec_y, font);
            cells[i][j] = std::move(cell);
        }
    }
}

auto getInput(unsigned int letter) -> void {
    char letter_char = static_cast<char> (letter);
    words[attempt][pos] = std::string(1, letter_char);
    cells[attempt][pos].text(std::string(1, toupper(letter_char)));
}

auto paintCells(const std::string &entered, const std::string &correct) -> void {
    for (int j = 0; j < LETTERS_NUMBER; ++j) {
        char letter = entered[j];
        if (correct.find(letter) == std::string::npos) continue;
        bool correct_place = correct.find(letter) == entered.find(letter) ||
                             correct.find(letter) == entered.rfind(letter);
        cells[attempt][j].paint(correct_place ? GREEN : YELLOW, 0);
    }
}

int main() {
    font.loadFromFile("../Fonts/Sono-Medium.ttf");

    auto word = createWord();
    auto answer = createText(word, 24, BLACK, 520, 900);

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Wordle");
    window.setKeyRepeatEnabled(false);

    initializeCells();

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

                        case sf::Keyboard::Tab:
                            answer.setFillColor(!show_correct ? GREEN : BLACK);
                            show_correct = !show_correct;
                            break;

                        case sf::Keyboard::Enter: {
                            auto entered = std::string();
                            for (const auto &l: words[attempt])
                                entered += l;

                            if (pos!= LETTERS_NUMBER || !WORDLIST.contains(entered)) {
                                std::cout << "\nNO SUCH WORD!\n";
                                break;
                            }

                            paintCells(entered, word);
                            ++attempt;
                            pos = 0;
                            bool correct = (entered == word);
                            if (correct) {
                                std::cout << "\nYOU WIN";
                                window.close();
                            }


                            if (attempt == WORDS_NUMBER) {
                                std::cout << "\nYOU LOST! \nRight answer was " << word;
                                window.close();
                            }
                            break;
                        }
                        case sf::Keyboard::BackSpace: {
                            if (pos <= 0) break;

                            std::cout << "del ";
                            words[attempt][pos - 1].clear();
                            cells[attempt][pos - 1].text("");
                            --pos;
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }

                case sf::Event::TextEntered: {
                    auto unicode = event.text.unicode;
                    if (!(64 < unicode && unicode < 123) || pos >= LETTERS_NUMBER) break;
                    std::cout << unicode << " ";
                    getInput(unicode);
                    ++pos;
                }
                default:
                    break;
            }
        }
        window.clear();
        drawCells(cells, window);
        window.draw(answer);
        window.display();
    }
}
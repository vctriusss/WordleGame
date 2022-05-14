#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <cctype>
#include "../Wordlist/wordlist.cpp"
//#include <spdlog/spdlog.h>

#define Table std::vector<std::vector<Cell>>

int HEIGHT = 90, WIDTH = 90;
sf::Font font;
int attempt = 0;
int col = 0;
bool show_correct = false;


struct Cell {
    sf::RectangleShape cell;
    sf::Text letter;
    sf::Color color = sf::Color::Black;
    int lx;
    int ly;
};

std::vector<std::vector<std::string>> words(6, std::vector<std::string>(5, std::string()));
Table cells(6, std::vector<Cell>(5, Cell()));

const int COLUMN_NUMBER = 5;
const int WORDS_NUMBER = 6;

auto createWord() -> std::string {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int t = rng() % wordlist.size();
    auto it = wordlist.begin();
    for (int k = 0; k < t; ++k) it++;
    return *it;
}

auto drawCells(const Table &table, sf::RenderWindow &window) -> void {
    for (const auto &v: table) {
        for (const auto &c: v) {
            window.draw(c.cell);
            window.draw(c.letter);
        }
    }
}

auto createText(std::string string, int size, sf::Color color, int x, int y) -> sf::Text {
    auto text = sf::Text(string, font, size);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(color);
    return text;
}

auto initializeCells() -> void {
    for (int i = 0; i < WORDS_NUMBER; ++i) {
        for (int j = 0; j < COLUMN_NUMBER; ++j) {
            Cell &curr = cells[i][j];
            int rec_x = 70 + (WIDTH + 10) * j;
            int rec_y = 50 + (HEIGHT + 20) * i;
            curr.cell.setSize(sf::Vector2f(WIDTH, HEIGHT));
            curr.cell.setPosition(sf::Vector2f(rec_x, rec_y));
            curr.cell.setFillColor(sf::Color::Black);
            curr.cell.setOutlineThickness(3);
            curr.cell.setOutlineColor(sf::Color(128, 128, 128));
            curr.lx = rec_x + WIDTH / 2 - 20;
            curr.ly = rec_y + HEIGHT / 2 - 50;

            curr.letter = createText("", 70, sf::Color::White, curr.lx, curr.ly);
        }
    }
}

auto getInput(sf::Uint32 letter) -> void {
    char letter_char = static_cast<char> (letter);
    char upper_letter_char = toupper(letter_char);
    auto new_letter = std::string(1, letter_char);
    words[attempt][col] = new_letter;
    cells[attempt][col].letter.setString(std::string(1, upper_letter_char));
}

auto colorizeCells(const std::string &new_word, const std::string &correct_word) -> void {
    for (int j = 0; j < 5; ++j) {
        char letter = new_word[j];
        if (correct_word.find(letter) != std::string::npos) {
            if (correct_word.find(letter) == new_word.find(letter)) {
                cells[attempt][j].cell.setFillColor(sf::Color(76, 153, 0));
            } else
                cells[attempt][j].cell.setFillColor(sf::Color(204, 204, 0));
            cells[attempt][j].cell.setOutlineThickness(0);
        }
    }
}

int main() {
    auto word = createWord();
    font.loadFromFile("../Fonts/Sono-Medium.ttf");
    sf::Text right_answer;
    right_answer = createText(word, 24, sf::Color::Black, 520, 900);

    sf::RenderWindow window(sf::VideoMode(640, 960), "Wordle");
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
                            right_answer.setFillColor(!show_correct ? sf::Color::Green : sf::Color::Black);
                            show_correct = !show_correct;
                            break;

                        case sf::Keyboard::Enter: {
                            if (col != 5) break;

                            std::string entered = "";
                            for (auto l: words[attempt]) {
                                entered += l;
                            }
                            if (wordlist.contains(entered)) {
                                colorizeCells(entered, word);
                                ++attempt;
                                col = 0;
                                bool correct = (entered == word);
                                if (correct) {
                                    std::cout << "\nYOU WIN";
                                    window.close();
                                }
                            } else
                                std::cout << "\nNO SUCH WORD!\n";

                            if (attempt == 6) {
                                std::cout << "\nYOU LOST!";
                                window.close();
                            }
                            break;
                        }
                        case sf::Keyboard::BackSpace: {
                            if (col <= 0) break;

                            std::cout << "del ";
                            words[attempt][col - 1] = "";
                            cells[attempt][col - 1].letter.setString("");
                            --col;
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }

                case sf::Event::TextEntered: {
                    if (!std::isalpha(event.text.unicode) || col >= COLUMN_NUMBER) break;

                    std::cout << event.text.unicode << " ";
                    getInput(event.text.unicode);
                    ++col;
                }
                default:
                    break;
            }
        }
        window.clear();
        drawCells(cells, window);
        window.draw(right_answer);
        window.display();
    }
}
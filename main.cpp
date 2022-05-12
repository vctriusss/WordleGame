#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include "WordsDB/words.cpp"

#define Table std::vector<std::vector<Cell>>

int HEIGHT = 90, WIDTH = 90;
sf::Font font;
int attempt = 0;
int col = 0;

struct Cell {
    sf::RectangleShape cell;
    sf::Text letter;
    sf::Color color = sf::Color::Black;
    int lx;
    int ly;
};
std::vector<std::vector<std::string>> words(6, std::vector<std::string>(5, std::string()));
Table cells(6, std::vector<Cell>(5, Cell()));


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

auto initializeCells() -> void {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            Cell& curr = cells[i][j];
            int rec_x = 70 + (WIDTH + 10) * j;
            int rec_y = 50 + (HEIGHT + 20) * i;
            curr.cell.setSize(sf::Vector2f(WIDTH, HEIGHT));
            curr.cell.setPosition(sf::Vector2f(rec_x, rec_y));
            curr.cell.setFillColor(sf::Color::Black);
            curr.cell.setOutlineThickness(3);
            curr.cell.setOutlineColor(sf::Color(128, 128, 128));
            curr.lx = rec_x + WIDTH / 2 - 20;
            curr.ly = rec_y + HEIGHT / 2 - 50;

            curr.letter.setFont(font);
            curr.letter.setFillColor(sf::Color::White);
            curr.letter.setString("");
            curr.letter.setCharacterSize(70);
            curr.letter.setPosition(sf::Vector2f(curr.lx, curr.ly));
        }
    }
}
auto getInput(sf::Uint32 letter) -> void {
    locale locale{""};
    auto letter_char = static_cast<char> (letter);
    auto new_letter = std::string(1, letter_char);
    words[attempt][col] = new_letter;
    cells[attempt][col].letter.setString(new_letter);
}

int main() {
    auto word = createWord();
    font.loadFromFile("../Fonts/Sono-Medium.ttf");
    sf::Text right_answer;
    bool flag = false;
    right_answer.setFont(font);
    right_answer.setString(word);
    right_answer.setPosition(520, 900);
    right_answer.setFillColor(sf::Color::Black);
    right_answer.setCharacterSize(24);
    sf::RenderWindow window(sf::VideoMode(640, 960), "Wordle");

    initializeCells();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 123 && event.text.unicode > 64 && col < 5) {
                    std::cout << event.text.unicode << " ";
                    getInput(event.text.unicode);
                    ++col;
                }
                else if (event.text.unicode  == 8 and col > 0) {
                    std::cout << "del";
                    words[attempt][col - 1] = "";
                    cells[attempt][col - 1].letter.setString("");
                    --col;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                if (!flag) {
                    right_answer.setFillColor(sf::Color::Green);
                    flag = true;
                } else {
                    right_answer.setFillColor(sf::Color::Black);
                    flag = false;
                }
            }
        }
        window.clear();
        drawCells(cells, window);
        window.draw(right_answer);
        window.display();
    }
}
#include "Game.hpp"
#include <iostream>
#include "functions.hpp"

/*
 * default constructor of a game*/
Game::Game() {
    font.loadFromFile("../Fonts/Sono-Medium.ttf");
    clear();
}

void Game::clear() {
    running = true;
    word = createWord();
    pos = 0;
    attempt = 0;
    words = Table(WORDS_NUMBER, std::vector<std::string>(LETTERS_NUMBER, std::string()));
    cells = Grid(WORDS_NUMBER, std::vector<Cell>(LETTERS_NUMBER));
}

void Game::initCells() {
    for (int i = 0; i < WORDS_NUMBER; ++i) {
        for (int j = 0; j < LETTERS_NUMBER; ++j) {
            int rec_x = 70 + (WIDTH + 10) * j;
            int rec_y = 50 + (HEIGHT + 20) * i;
            auto cell = Cell(rec_x, rec_y, font, "");
            cells[i][j] = std::move(cell);
        }
    }
}

void Game::initTextBoxes() {
    bottom_text = createTextBox("", font, 40, BLACK, WIN_WIDTH / 2, WIN_HEIGHT - 250);
    right_answer_text = createTextBox(RIGHT_ANSWER + word, font, 40, BLACK, WIN_WIDTH / 2, WIN_HEIGHT - 175);
    restart_text = createTextBox(PRESS_TO_RESTART, font, 40, BLACK, WIN_WIDTH / 2, WIN_HEIGHT - 100);
}

void Game::drawObjects(sf::RenderWindow &window) {
    for (auto &v: cells) {
        for (auto &c: v) {
            c.draw(window);
            window.draw(bottom_text);
            window.draw(right_answer_text);
            window.draw(restart_text);
        }
    }
}

void Game::showTextBox(sf::Text &textBox, std::string new_text = "", const sf::Color &new_color = WHITE) {
    if (new_text.empty()) new_text = textBox.getString();
    int len = new_text.size();
    sf::Vector2f position = textBox.getPosition();
    textBox.setPosition(WIN_WIDTH / 2 - (textBox.getCharacterSize() / 3 - 1) * len, position.y);
    textBox.setString(new_text);
    textBox.setFillColor(new_color);
}

void Game::getInput(const unsigned int &letter) {
    char letter_char = static_cast<char> (letter);
    words[attempt][pos] = std::string(1, letter_char);
    cells[attempt][pos].setLetter(std::string(1, toupper(letter_char)));
    ++pos;
}

void Game::eraseSymbol() {
    if (pos <= 0) return;
    --pos;
    words[attempt][pos].clear();
    cells[attempt][pos].setLetter();
}

void Game::paintCells(const std::string &entered, const std::string &correct) {
    for (int j = 0; j < LETTERS_NUMBER; ++j) {
        char letter = entered[j];
        if (correct.find(letter) == std::string::npos) {
            cells[attempt][j].paint(GRAY, 0);
            continue;
        }
        bool correct_place = correct.find(letter) == j || correct.rfind(letter) == j;
        cells[attempt][j].paint(correct_place ? GREEN : YELLOW, 0);
    }
}

void Game::run(sf::RenderWindow &window) {
    initTextBoxes();
    initCells();
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
                            std::cout << "HINT: " << word << std::endl;
                            break;

                        case sf::Keyboard::Enter: {
                            bottom_text.setFillColor(BLACK);
                            auto entered = std::string();
                            for (const auto &l: words[attempt])
                                entered += l;

                            if (displayError(entered)) break;

                            paintCells(entered, word);
                            ++attempt;
                            pos = 0;
                            bool correct = (entered == word);
                            if (correct || attempt == WORDS_NUMBER) EndGameScenario(correct);
                            break;
                        }
                        case sf::Keyboard::Tab: {
                            if (!running) restart(window);
                            break;
                        }
                        case sf::Keyboard::BackSpace: {
                            bottom_text.setFillColor(BLACK);
                            eraseSymbol();
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
                    getInput(unicode);
                    break;
                }
                default:
                    break;
            }
        }
        window.clear(BLACK);
        drawObjects(window);
        window.display();
    }
}

void Game::restart(sf::RenderWindow &window) {
    clear();
    run(window);
}

bool Game::displayError(const std::string &entered) {
    if (pos != LETTERS_NUMBER) {
        showTextBox(bottom_text, NOT_ENOUGH);
        return true;
    }
    if (!WORDLIST.contains(entered)) {
        showTextBox(bottom_text, NOT_IN_WORDLIST);
        return true;
    }
    return false;
}

void Game::EndGameScenario(bool correct) {
    running = false;
    showTextBox(bottom_text, correct ? "YOU WIN!" : "YOU LOST", correct ? GREEN : RED);
    if (!correct) showTextBox(right_answer_text);
    showTextBox(restart_text);
}

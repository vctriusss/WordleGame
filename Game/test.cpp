#include <doctest.h>
#include "functions.hpp"
#include "Game.hpp"

TEST_CASE ("doctest works properly") {
            REQUIRE(1 + 2 == 3);
}

TEST_CASE ("entered symbol is in english alphabet") {
    char A = 'A';
    char b = 'b';
    char bracket = ']';

    int A_unicode = A;
    int b_unicode = b;
    int bracket_unicode = bracket;

            REQUIRE(isEnglish(A_unicode) == true);
            REQUIRE(isEnglish(b_unicode) == true);
            REQUIRE(isEnglish(bracket_unicode) == false);
}

TEST_CASE ("random picked word is in wordlist") {
    auto word = createWord();
            REQUIRE(WORDLIST.contains(word));
}

TEST_CASE ("correct painting (hard cases)") {
    auto game = Game();
    std::string ans = "horny";
    std::string input = "lorry";
    int attempt = 0;
    game.cells[attempt] = std::vector<Cell>{Cell(), Cell(), Cell(), Cell(), Cell()};
    game.paintCells(input, ans);
            REQUIRE(game.cells[attempt][0].rect.getFillColor() == GRAY);
            REQUIRE(game.cells[attempt][1].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][2].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][3].rect.getFillColor() == YELLOW);
            REQUIRE(game.cells[attempt][4].rect.getFillColor() == GREEN);
    ans = "spoon";
    input = "spook";
    game.paintCells(input, ans);
            REQUIRE(game.cells[attempt][0].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][1].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][2].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][3].rect.getFillColor() == GREEN);
            REQUIRE(game.cells[attempt][4].rect.getFillColor() == GRAY);
}

TEST_CASE ("correct error displaying") {
    auto game = Game();
    std::string ent_notenough = "asdf";
    std::string ent_notexists = "ooooo";
    std::string ent_correct = "slate";
    game.pos = 4;
            REQUIRE(game.displayError(ent_notenough) == true);
    game.pos = 5;
            REQUIRE(game.displayError(ent_notexists) == true);
            REQUIRE(game.displayError(ent_correct) == false);
}

TEST_CASE ("correct delete processing") {
    auto game = Game();
    sf::Font font;
    game.words = Table{std::vector<std::string>{"s", "l", "a", "t", "e"},
                       std::vector<std::string>{"a", "", "", "", ""},
                       std::vector<std::string>(),
                       std::vector<std::string>(),
                       std::vector<std::string>()};
    game.cells = Grid{std::vector<Cell>{5, Cell()},
                      std::vector<Cell>{Cell(0, 0, font, "A"), Cell(), Cell(), Cell(), Cell()},
                      std::vector<Cell>{5, Cell()},
                      std::vector<Cell>{5, Cell()},
                      std::vector<Cell>{5, Cell()},
                      std::vector<Cell>{5, Cell()}};
    game.attempt = 1;
    game.pos = 1;

    game.eraseSymbol();
            REQUIRE(game.words == Table{std::vector<std::string>{"s", "l", "a", "t", "e"},
                                        std::vector<std::string>{"", "", "", "", ""},
                                        std::vector<std::string>(),
                                        std::vector<std::string>(),
                                        std::vector<std::string>()});

    game.eraseSymbol();
            REQUIRE(game.words == Table{std::vector<std::string>{"s", "l", "a", "t", "e"},
                                        std::vector<std::string>{"", "", "", "", ""},
                                        std::vector<std::string>(),
                                        std::vector<std::string>(),
                                        std::vector<std::string>()});

}
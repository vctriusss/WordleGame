#include "Game.hpp"
#include "functions.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Wordle");
    window.setKeyRepeatEnabled(false);
    Game game = Game();
    game.run(window);
}

/*
 what can be tested:
  - entering text(creating sf::Event::TextEntered and check if input is get)
  - painting cells (depending on entered word)
  - deleting setLetter
  - showing error messages
  README.md
*/
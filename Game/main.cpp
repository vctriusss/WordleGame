#include "Game.hpp"
#include "functions.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Wordle");
    window.setKeyRepeatEnabled(false);
    Game game = Game();
    game.run(window);
}

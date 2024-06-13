#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.hpp>
#include "game2048.h"
#include "constant.h"

#define CELL_SIZE 80
#define WINDOW_SIZE (CELL_SIZE * SIZE)

void display(const game2048& game, sf::RenderWindow& window, const sf::Font& font, int alpha);
int displayLosing(sf::RenderWindow& window, const sf::Font& font, bool UnRedo);
// -1: Try again
// 0: Exit to main menu
// 1: Undo
int displayWinning(sf::RenderWindow& window, const sf::Font& font);
// 0: Exit to main menu
// 1: Continue

#endif // !DISPLAY

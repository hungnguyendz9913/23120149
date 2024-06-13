#include <iostream>
#include <string>
#include "display.h"
#include "playGame.h"

using namespace std;

sf::Color getColor(int number, int alpha) {
    switch (number) {
    case 2: return sf::Color(238, 228, 218, alpha);
    case 4: return sf::Color(237, 224, 200, alpha);
    case 8: return sf::Color(242, 177, 121, alpha);
    case 16: return sf::Color(245, 149, 99, alpha);
    case 32: return sf::Color(246, 124, 95, alpha);
    case 64: return sf::Color(246, 94, 59, alpha);
    case 128: return sf::Color(237, 207, 114, alpha);
    case 256: return sf::Color(237, 204, 97, alpha);
    case 512: return sf::Color(237, 200, 80, alpha);
    case 1024: return sf::Color(237, 197, 63, alpha);
    case 2048: return sf::Color(237, 194, 46, alpha);
    default: return sf::Color(205, 193, 180, alpha);
    }
}

void display(const game2048& game, sf::RenderWindow& window, const sf::Font& font, int alpha) {
    window.clear(sf::Color::White);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int index = i * SIZE + j;
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 5, CELL_SIZE - 5));
            cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            cell.setFillColor(getColor(game.board[index], alpha));
            window.draw(cell);

            if (game.board[index] != 0) {
                sf::Text number;
                number.setFont(font);
                number.setString(std::to_string(game.board[index]));
                number.setCharacterSize(30);
                number.setFillColor(sf::Color(0, 0, 0, alpha));

                sf::FloatRect textRect = number.getLocalBounds();
                number.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                number.setPosition(i * CELL_SIZE + CELL_SIZE / 2, j * CELL_SIZE + CELL_SIZE / 2);

                window.draw(number);
            }
        }
    }

    sf::Text currentScore;
    currentScore.setFont(font);
    currentScore.setString("Score: " + std::to_string(game.score));
    currentScore.setCharacterSize(30);
    currentScore.setFillColor(sf::Color(0, 0, 0, alpha));
    currentScore.setPosition(10, WINDOW_SIZE + 10);
    window.draw(currentScore);

    window.display();
}

int displayLosing(sf::RenderWindow& window, const sf::Font& font, bool UnRedo) {
    sf::Text text;
    text.setFont(font);
    text.setString("Game Over!");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color(0, 0, 0, 255));

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f - 70);

    sf::Text tryAgainButton;
    tryAgainButton.setFont(font);
    tryAgainButton.setString("Try Again");
    tryAgainButton.setCharacterSize(30);
    tryAgainButton.setFillColor(sf::Color(0, 0, 0, 255));

    sf::FloatRect tryAgainRect = tryAgainButton.getLocalBounds();
    tryAgainButton.setPosition(WINDOW_SIZE - tryAgainRect.width - 50, WINDOW_SIZE / 2.0f);

    sf::Text exitButton;
    exitButton.setFont(font);
    exitButton.setString("Exit to Main Menu");
    exitButton.setCharacterSize(30);
    exitButton.setFillColor(sf::Color(0, 0, 0, 255));

    sf::FloatRect exitRect = exitButton.getLocalBounds();
    exitButton.setPosition(WINDOW_SIZE - exitRect.width - 50, WINDOW_SIZE / 2.0f + 50);

    sf::Text undoButton;
    if (UnRedo) {
        undoButton.setFont(font);
        undoButton.setString("Undo");
        undoButton.setCharacterSize(30);
        undoButton.setFillColor(sf::Color(0, 0, 0, 255));

        sf::FloatRect undoRect = undoButton.getLocalBounds();
        undoButton.setPosition(WINDOW_SIZE - undoRect.width - 50, WINDOW_SIZE / 2.0f + 100);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (tryAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    //window.close();
                    return -1;
                }

                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return 0;
                }

                if (UnRedo && undoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return 1;
                }
            }

            window.draw(text);
            window.draw(tryAgainButton);
            window.draw(exitButton);
            if (UnRedo) {
                window.draw(undoButton);
            }
            window.display();
        }
    }

    return 0;
}

int displayWinning(sf::RenderWindow& window, const sf::Font& font) {
    std::cout << "Winning display\n";

    sf::Text winningText;
    winningText.setFont(font);
    winningText.setString("Winner!");
    winningText.setCharacterSize(50);
    winningText.setFillColor(sf::Color::Black);

    sf::FloatRect winningTextRect = winningText.getLocalBounds();
    winningText.setOrigin(winningTextRect.left + winningTextRect.width / 2.0f,
        winningTextRect.top + winningTextRect.height / 2.0f);
    winningText.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f - 50);

    sf::Text exitButton;
    exitButton.setFont(font);
    exitButton.setString("Exit to Main Menu");
    exitButton.setCharacterSize(30);
    exitButton.setFillColor(sf::Color::Black);

    sf::FloatRect exitRect = exitButton.getLocalBounds();
    exitButton.setOrigin(exitRect.left + exitRect.width / 2.0f,
        exitRect.top + exitRect.height / 2.0f);
    exitButton.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f + 150);

    sf::Text continueButton;
    continueButton.setFont(font);
    continueButton.setString("Continue");
    continueButton.setCharacterSize(30);
    continueButton.setFillColor(sf::Color::Black);

    sf::FloatRect continueRect = continueButton.getLocalBounds();
    continueButton.setOrigin(continueRect.left + continueRect.width / 2.0f,
        continueRect.top + continueRect.height / 2.0f);
    continueButton.setPosition(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f + 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        return 0;
                    }

                    if (continueButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        return 1;
                    }
                }
            }
        }

        window.draw(winningText);
        window.draw(exitButton);
        window.draw(continueButton);

        window.display();
    }

    return 1;
}

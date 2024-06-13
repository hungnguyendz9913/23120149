#include <SFML/Graphics.hpp>
#include <iostream>
#include "constant.h"

const int MENU_WIDTH = 800;
const int MENU_HEIGHT = 400;
const int CELL_SIZE = 70;

void displaySetting(sf::RenderWindow& window, const sf::Font& font) {
    window.setSize(sf::Vector2u(MENU_WIDTH, MENU_HEIGHT));

    sf::Text bsize;
    bsize.setFont(font);
    bsize.setString("Select Board Size:");
    bsize.setCharacterSize(40);
    bsize.setFillColor(sf::Color::Black);
    bsize.setStyle(sf::Text::Bold);
    bsize.setPosition((MENU_WIDTH - 400) / 2, 50);

    sf::RectangleShape cells[7];
    sf::Text cellTexts[7];

    for (int i = 0; i < 7; ++i) {
        cells[i].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        cells[i].setFillColor(sf::Color::White);
        cells[i].setOutlineColor(sf::Color::Black);
        cells[i].setOutlineThickness(2);
        cells[i].setPosition((MENU_WIDTH - 7 * CELL_SIZE) / 2 + i * (CELL_SIZE + 10) - 50, 130);

        cellTexts[i].setFont(font);
        cellTexts[i].setString(std::to_string(4 + i) + "x" + std::to_string(4 + i));
        cellTexts[i].setCharacterSize(24);
        cellTexts[i].setFillColor(sf::Color::Black);
        sf::FloatRect textRect = cellTexts[i].getLocalBounds();
        cellTexts[i].setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        cellTexts[i].setPosition(cells[i].getPosition().x + CELL_SIZE / 2,
            cells[i].getPosition().y + CELL_SIZE / 2);
    }

    sf::Text unredo;
    unredo.setFont(font);
    unredo.setString("UndoRedo Setting:");
    unredo.setCharacterSize(40);
    unredo.setFillColor(sf::Color::Black);
    unredo.setStyle(sf::Text::Bold);
    unredo.setPosition(105, 250);

    sf::RectangleShape yes;
    sf::Text yesText;

    yes.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    yes.setFillColor(sf::Color::White);
    yes.setOutlineColor(sf::Color::Black);
    yes.setOutlineThickness(2);
    yes.setPosition(475, 245);

    yesText.setFont(font);
    yesText.setString("yes");
    yesText.setCharacterSize(24);
    yesText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = yesText.getLocalBounds();
    yesText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    yesText.setPosition(yes.getPosition().x + CELL_SIZE / 2,
        yes.getPosition().y + CELL_SIZE / 2);

    sf::RectangleShape no;
    sf::Text noText;

    no.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    no.setFillColor(sf::Color::White);
    no.setOutlineColor(sf::Color::Black);
    no.setOutlineThickness(2);
    no.setPosition(555, 245);

    noText.setFont(font);
    noText.setString("no");
    noText.setCharacterSize(24);
    noText.setFillColor(sf::Color::Black);
    textRect = noText.getLocalBounds();
    noText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    noText.setPosition(no.getPosition().x + CELL_SIZE / 2,
        no.getPosition().y + CELL_SIZE / 2);

    noText.setFont(font);
    noText.setString("no");
    noText.setCharacterSize(24);
    noText.setFillColor(sf::Color::Black);
    textRect = noText.getLocalBounds();
    noText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    noText.setPosition(no.getPosition().x + CELL_SIZE / 2,
        no.getPosition().y + CELL_SIZE / 2);

    sf::RectangleShape exitButton;
    sf::Text exitText;

    exitButton.setSize(sf::Vector2f(100, 60));
    exitButton.setFillColor(sf::Color::White);
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setPosition(350, 310);

    exitText.setFont(font);
    exitText.setString("EXIT");
    exitText.setCharacterSize(24);
    exitText.setStyle(sf::Text::Bold);
    exitText.setFillColor(sf::Color::Black);
    textRect = exitText.getLocalBounds();
    exitText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    exitText.setPosition(exitButton.getPosition().x + 50,
        exitButton.getPosition().y + 30);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < 7; ++i) {
                        if (cells[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            SIZE = 4 + i;
                            std::cout << "Selected size: " << SIZE << "x" << SIZE << std::endl;
                        }
                    }
                    if (yes.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        UnRedo = true;
                        std::cout << "Undo/Redo Allowed\n";
                    }
                    if (no.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        UnRedo = false;
                        std::cout << "Undo/Redo Prohibited\n";
                    }
                    if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "settings completed\n";
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(bsize);
        for (int i = 0; i < 7; ++i) {
            window.draw(cells[i]);
            window.draw(cellTexts[i]);
        }
        window.draw(unredo);
        window.draw(yes);
        window.draw(yesText);
        window.draw(no);
        window.draw(noText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }
}

void displaySettings() {
    sf::RenderWindow window(sf::VideoMode(MENU_WIDTH, MENU_HEIGHT), "2048 Menu");

    sf::Font font;
    if (!font.loadFromFile("OpenSans-Italic.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    displaySetting(window, font);
}

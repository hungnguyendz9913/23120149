#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <iostream>
#include "vector.h"
using namespace std;

void displayTlist(vectorh<pair<string, int>> Tlist) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Top 2048 Players");

    sf::Font font;
    if (!font.loadFromFile("OpenSans.ttf")) {
        cerr << "Error loading font\n";
        return;
    }

    sf::Color backgroundColor(222, 184, 135);

    auto isMouseOverButton = [](const sf::Text& button, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        };

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Top Score");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    titleText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 50.0f));

    sf::Text exitButton;
    exitButton.setFont(font);
    exitButton.setString("Exit to Main Menu");
    exitButton.setCharacterSize(50);
    exitButton.setFillColor(sf::Color::Black);
    sf::FloatRect exitRect = exitButton.getLocalBounds();
    exitButton.setOrigin(exitRect.left + exitRect.width / 2.0f,
        exitRect.top + exitRect.height / 2.0f);
    exitButton.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y - 70.0f));

    sf::RectangleShape exitFrame;
    exitFrame.setSize(sf::Vector2f(exitRect.width + 20, exitRect.height + 20));
    exitFrame.setFillColor(sf::Color::Transparent);
    exitFrame.setOutlineThickness(2);
    exitFrame.setOutlineColor(sf::Color::Black);
    exitFrame.setOrigin(exitFrame.getSize() / 2.0f);
    exitFrame.setPosition(exitButton.getPosition());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isMouseOverButton(exitButton, window)) {
                        window.close();
                    }
                }
            }
        }

        window.clear(backgroundColor);

        window.draw(titleText);

        float startY = 150.0f;
        float lineHeight = 30.0f;
        for (size_t i = 0; i < Tlist.size(); i += 2) {
            sf::Text text1;
            text1.setFont(font);
            text1.setString(to_string(i + 1) + ". " + Tlist[i].first + "-" + to_string(Tlist[i].second));
            text1.setCharacterSize(30);
            text1.setFillColor(sf::Color::Black);
            sf::FloatRect textRect1 = text1.getLocalBounds();
            text1.setOrigin(textRect1.left + textRect1.width / 2.0f,
                textRect1.top + textRect1.height / 2.0f);
            text1.setPosition(sf::Vector2f(window.getSize().x / 4.0f, startY + i / 2 * lineHeight));

            window.draw(text1);

            if (i + 1 < Tlist.size()) {
                sf::Text text2;
                text2.setFont(font);
                text2.setString(to_string(i + 2) + ". " + Tlist[i + 1].first + "-" + to_string(Tlist[i + 1].second));
                text2.setCharacterSize(30);
                text2.setFillColor(sf::Color::Black);
                sf::FloatRect textRect2 = text2.getLocalBounds();
                text2.setOrigin(textRect2.left + textRect2.width / 2.0f,
                    textRect2.top + textRect2.height / 2.0f);
                text2.setPosition(sf::Vector2f(3 * window.getSize().x / 4.0f, startY + i / 2 * lineHeight));

                window.draw(text2);
            }
        }

        window.draw(exitFrame);
        window.draw(exitButton);

        window.display();
    }
}

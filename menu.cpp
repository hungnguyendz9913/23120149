#include "menu.h"
#include "playGame.h"
#include "constant.h"
#include "settings.h"
#include "getUsername.h"
#include "topList.h"
#include "resume.h"
#include "constant.h"

void displayMenu(sf::RenderWindow& window, const sf::Font& font) {
    vectorh<pair<string, int> > Tlist;
    readTop20List(Tlist);
    vectorh<Info> data = readDataResume();
    int canResume = data.size();
    int alpha = (canResume > 0 ? 255 : 100);
    vectorh<pair<string, int> > Rlist;
    for (auto ch : data) {
        Rlist.push_back({ ch.username, 0 });
    }

    sf::Text title;
    title.setFont(font);
    title.setString("2048 Game Menu");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition((MENU_SIZE - MENU_WIDTH) / 2, 50);

    sf::RectangleShape newGameButton(sf::Vector2f(300, 50));
    newGameButton.setFillColor(sf::Color::Green);
    newGameButton.setPosition((MENU_SIZE - 300) / 2, 150);

    sf::Text newGameText;
    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setCharacterSize(24);
    newGameText.setFillColor(sf::Color::Black);
    sf::FloatRect newGameTextRect = newGameText.getLocalBounds();
    newGameText.setOrigin(newGameTextRect.left + newGameTextRect.width / 2.0f, newGameTextRect.top + newGameTextRect.height / 2.0f);
    newGameText.setPosition(MENU_SIZE / 2, 175);

    sf::RectangleShape settingButton(sf::Vector2f(300, 50));
    settingButton.setFillColor(sf::Color::Blue);
    settingButton.setPosition((MENU_SIZE - 300) / 2, 225);

    sf::Text settingText;
    settingText.setFont(font);
    settingText.setString("Game Setting");
    settingText.setCharacterSize(24);
    settingText.setFillColor(sf::Color::Black);
    sf::FloatRect settingTextRect = settingText.getLocalBounds();
    settingText.setOrigin(settingTextRect.left + settingTextRect.width / 2.0f, settingTextRect.top + settingTextRect.height / 2.0f);
    settingText.setPosition(MENU_SIZE / 2, 250);

    sf::RectangleShape tlistButton(sf::Vector2f(300, 50));
    tlistButton.setFillColor(sf::Color::Red);
    tlistButton.setPosition((MENU_SIZE - 300) / 2, 300);

    sf::Text tlistText;
    tlistText.setFont(font);
    tlistText.setString("Top 20 List");
    tlistText.setCharacterSize(24);
    tlistText.setFillColor(sf::Color::Black);
    sf::FloatRect tlistTextRect = tlistText.getLocalBounds();
    tlistText.setOrigin(tlistTextRect.left + tlistTextRect.width / 2.0f, tlistTextRect.top + tlistTextRect.height / 2.0f);
    tlistText.setPosition(MENU_SIZE / 2, 325);

    sf::RectangleShape resumeButton(sf::Vector2f(300, 50));
    resumeButton.setFillColor(sf::Color(255, 255, 0, alpha));
    resumeButton.setPosition((MENU_SIZE - 300) / 2, 375);

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color(0, 0, 0, alpha));
    sf::FloatRect resumeTextRect = resumeText.getLocalBounds();
    resumeText.setOrigin(resumeTextRect.left + resumeTextRect.width / 2.0f, resumeTextRect.top + resumeTextRect.height / 2.0f);
    resumeText.setPosition(MENU_SIZE / 2, 400);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (newGameButton.getGlobalBounds().contains(mousePosF)) {
                    window.close();
                    string username = getUsername(Tlist, Rlist);
                    int score = play(username);
                    if (score > 0) {
                        Tlist.push_back({ username, score });
                        writeTop20List(Tlist);
                    }
                    Tlist.clear();
                    Rlist.clear();
                    data.clear();
                    menu();
                }

                if (settingButton.getGlobalBounds().contains(mousePosF)) {
                    displaySettings();
                }

                if (tlistButton.getGlobalBounds().contains(mousePosF)) {
                    displayTlist(Tlist);
                }

                if (resumeButton.getGlobalBounds().contains(mousePosF) && canResume) {
                    window.close();
                    Info inf = displayResume(data);
                    if (inf == EMPTY) {
                        menu();
                    }
                    else {
                        writeDataResume(data);
                        SIZE = inf.size;
                        UnRedo = inf.canUndo;
                        play(inf.username, inf.gameState);
                        Tlist.clear();
                        Rlist.clear();
                        data.clear();
                        SIZE = 4;
                        UnRedo = false;
                        menu();
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(title);
        window.draw(newGameButton);
        window.draw(newGameText);
        window.draw(settingButton);
        window.draw(settingText);
        window.draw(tlistButton);
        window.draw(tlistText);
        window.draw(resumeButton);
        window.draw(resumeText);
        window.display();
    }
}

void menu() {
    sf::RenderWindow window(sf::VideoMode(MENU_HEIGHT, MENU_SIZE), "2048 Game");
    sf::Font font;
    if (!font.loadFromFile("Minecraft Evenings.ttf")) {
        return;
    }
    
    while (window.isOpen()) {
        displayMenu(window, font);
    }
}

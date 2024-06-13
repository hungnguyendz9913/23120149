#include "resume.h"

vectorh<Info> readDataResume() {
    vectorh<Info> data;
    ifstream file("resume.bin", ios::binary);
    if (file.is_open()) {
        while (file.peek() != EOF) {
            Info temp;
            int usernameSize;
            file.read(reinterpret_cast<char*>(&usernameSize), sizeof(usernameSize));
            temp.username.resize(usernameSize);
            file.read(&temp.username[0], usernameSize);
            file.read(reinterpret_cast<char*>(&temp.size), sizeof(temp.size));
            file.read(reinterpret_cast<char*>(&temp.canUndo), sizeof(temp.canUndo));
            file.read(reinterpret_cast<char*>(&temp.gameState.score), sizeof(temp.gameState.score));
            file.read(reinterpret_cast<char*>(&temp.gameState.step), sizeof(temp.gameState.step));
            temp.gameState.board = new int[temp.size * temp.size];
            file.read(reinterpret_cast<char*>(temp.gameState.board), temp.size * temp.size * sizeof(int));
            data.push_back(temp);
        }
        file.close();
    }
    return data;
}

void writeDataResume(const vectorh<Info>& data) {
    ofstream file("resume.bin", ios::binary | ios::trunc);
    if (file.is_open()) {
        for (const auto& item : data) {
            int usernameSize = item.username.size();
            file.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
            file.write(item.username.c_str(), usernameSize);
            file.write(reinterpret_cast<const char*>(&item.size), sizeof(item.size));
            file.write(reinterpret_cast<const char*>(&item.canUndo), sizeof(item.canUndo));
            file.write(reinterpret_cast<const char*>(&item.gameState.score), sizeof(item.gameState.score));
            file.write(reinterpret_cast<const char*>(&item.gameState.step), sizeof(item.gameState.step));
            file.write(reinterpret_cast<const char*>(item.gameState.board), item.size * item.size * sizeof(int));
        }
        file.close();
    }
}

void addInfo(const Info& newInfo) {
    vectorh<Info> data = readDataResume();
    if (data.size() < 5) {
        data.push_back(newInfo);
    }
    else {
        for (int i = 1; i < data.size(); ++i) {
            data[i - 1] = data[i];
        }
        data[data.size() - 1] = newInfo;
    }
    writeDataResume(data);
}

Info displayResume(vectorh<Info>& data) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Resume Game");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        exit(1);
    }

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color(50, 50, 50));

    sf::Text title("GAME RESUME", font, 50);
    title.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2, titleBounds.top + titleBounds.height / 2);
    title.setPosition(400, 75);

    std::vector<sf::Text> userTexts;
    std::vector<sf::RectangleShape> userBoxes;
    for (int i = 0; i < data.size(); ++i) {
        sf::RectangleShape box(sf::Vector2f(700, 50));
        box.setFillColor(sf::Color(100, 100, 100));
        box.setPosition(50, 150 + i * 60);

        sf::Text userText(data[i].username, font, 20);
        userText.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = userText.getLocalBounds();
        userText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        userText.setPosition(400, 150 + i * 60 + 25);

        userBoxes.push_back(box);
        userTexts.push_back(userText);
    }

    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(200, 0, 0));
    exitButton.setPosition(300, 500);

    sf::Text exitText("EXIT", font, 30);
    exitText.setFillColor(sf::Color::White);

    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setOrigin(exitBounds.left + exitBounds.width / 2, exitBounds.top + exitBounds.height / 2);
    exitText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2, exitButton.getPosition().y + exitButton.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < userBoxes.size(); ++i) {
                        if (userBoxes[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            Info result = data[i];
                            for (int j = i + 1; j < userBoxes.size(); j++) {
                                data[j - 1] = data[j];
                            }
                            data.pop_back();
                            return result;
                        }
                    }
                    if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        break;
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(title);
        for (const auto& box : userBoxes) {
            window.draw(box);
        }
        for (const auto& text : userTexts) {
            window.draw(text);
        }
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }

    return Info{};
}
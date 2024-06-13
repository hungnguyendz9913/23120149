#include "getUsername.h"

string rename(string& name) {
    transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return tolower(c); });

    name.erase(name.begin(), find_if(name.begin(), name.end(), [](unsigned char c) { return !isspace(c); }));
    name.erase(find_if(name.rbegin(), name.rend(), [](unsigned char c) { return !isspace(c); }).base(), name.end());

    auto new_end = unique(name.begin(), name.end(), [](char left, char right) { return isspace(left) && isspace(right); });
    name.erase(new_end, name.end());

    return name;
}

bool canFind(const string& inp, const vectorh<pair<string, int>> Tlist) {
    if (Tlist.size() == 0) return false;
    for (const auto& ch : Tlist) {
        if (ch.first == inp) return true;
    }
    return false;
}

string getUsername(vectorh<pair <string, int> > Tlist, vectorh<pair <string, int> > Rlist) {
    sf::RenderWindow window(sf::VideoMode(800, 300), "Enter Username");

    sf::Font font;
    if (!font.loadFromFile("OpenSans.ttf")) {
        cerr << "Could not load font\n";
        return "";
    }

    sf::Text placeholderText("Enter username:", font, 30);
    placeholderText.setFillColor(sf::Color(119, 110, 101, 150));
    sf::FloatRect placeholderBounds = placeholderText.getLocalBounds();
    placeholderText.setOrigin(placeholderBounds.left + placeholderBounds.width / 2.0f,
        placeholderBounds.top + placeholderBounds.height / 2.0f);
    placeholderText.setPosition(window.getSize().x / 2.0f, 100);

    sf::Text usernameText("", font, 30);
    usernameText.setFillColor(sf::Color(119, 110, 101));

    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color(246, 94, 59));
    button.setPosition(window.getSize().x / 2.0f - button.getSize().x / 2.0f, 200);

    sf::Text buttonText("Submit", font, 30);
    buttonText.setFillColor(sf::Color::White);
    sf::FloatRect buttonBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(buttonBounds.left + buttonBounds.width / 2.0f,
        buttonBounds.top + buttonBounds.height / 2.0f);
    buttonText.setPosition(window.getSize().x / 2.0f, 225);

    string username = "";
    bool validUsername = false;

    while (!validUsername) {
        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!username.empty()) {
                            username.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128) {
                        username += static_cast<char>(event.text.unicode);
                    }

                    if (username.empty()) {
                        placeholderText.setFillColor(sf::Color(119, 110, 101, 150));
                        usernameText.setString("");
                    }
                    else {
                        placeholderText.setFillColor(sf::Color(119, 110, 101, 0));
                        usernameText.setString(username);
                    }

                    sf::FloatRect textBounds = usernameText.getLocalBounds();
                    usernameText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
                    usernameText.setPosition(window.getSize().x / 2.0f, 100);
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    username = rename(username);
                    if (username.length() >= 3 && !canFind(username, Tlist) && !canFind(username, Rlist)) {
                        validUsername = true;
                        window.close();
                    }
                    else {
                        cout << "Invalid username entered: " << username << endl;
                        username.clear();
                        usernameText.setString("");
                        placeholderText.setFillColor(sf::Color(119, 110, 101, 150));
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            username = rename(username);
                            if (username.length() >= 3 && !canFind(username, Tlist) && !canFind(username, Rlist)) {
                                validUsername = true;
                                window.close();
                            }
                            else {
                                cout << "Invalid username entered: " << username << endl;
                                username.clear();
                                usernameText.setString("");
                                placeholderText.setFillColor(sf::Color(119, 110, 101, 150));
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color(250, 248, 239));
            window.draw(placeholderText);
            window.draw(usernameText);
            window.draw(button);
            window.draw(buttonText);
            window.display();
        }

        if (!validUsername) {
            window.create(sf::VideoMode(800, 300), "Enter Username");
        }
    }

    cout << "Valid username entered: " << username << endl;

    return username;
}

#include "game2048.h"
#include "stack.h"
#include "display.h"
#include "resume.h"
#include <conio.h>

using namespace std;

const int moody = 100;
const int bright = 255;

int play(const string& username) {
    stackh<game2048> stack;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + 100), "2048 Game");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return 0;
    }

    bool winner = stack.current().isWinning();
    display(stack.current(), window, font, bright);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            bool (game2048:: * resive)();
            if (event.type == sf::Event::KeyPressed) {
                //char ch;
                switch (event.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    stack.remove();
                    resive = &game2048::Left;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    stack.remove();
                    resive = &game2048::Right;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    stack.remove();
                    resive = &game2048::Up;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    stack.remove();
                    resive = &game2048::Down;
                    break;
                case sf::Keyboard::R:
                    if (!UnRedo) continue;
                    if (stack.go_back()) {
                        display(stack.current(), window, font, bright);
                    }
                    continue;
                case sf::Keyboard::U:
                    if (!UnRedo) continue;
                    if (stack.go_foward()) {
                        display(stack.current(), window, font, bright);
                    }
                    continue;
                case sf::Keyboard::E:
                    addInfo(Info{username, SIZE, UnRedo, stack.current()});
                    return -1;
                case sf::Keyboard::Q:
                    return stack.current().score;
                default:
                    resive = &game2048::Inactive;
                    break;
                }

                game2048 current = stack.current();
                if (current.moving(resive)) {
                    stack.push_back(current);
                    if (current.isLosing()) {
                        display(current, window, font, bright);
                        sf::sleep(sf::seconds(1));
                        display(current, window, font, moody);
                        display(current, window, font, moody);

                        int undo = displayLosing(window, font, UnRedo);
                        if (undo == -1) {
                            window.close();
                            return play(username);
                        }
                        else if (undo == 0) {
                            window.close();
                            return stack.current().score;
                        }
                        else {
                            stack.go_foward();
                            display(stack.current(), window, font, bright);
                        }
                    }
                    else if (current.isWinning() && winner == false) {
                        winner = true;
                        display(current, window, font, bright);
                        sf::sleep(sf::seconds(1));
                        display(current, window, font, moody);
                        display(current, window, font, moody);
                        int winner = displayWinning(window, font);
                        if (winner == 0) {
                            window.close();
                            addInfo(Info{ username, SIZE, UnRedo, stack.current() });
                            return -1;
                        }
                        else {
                            display(current, window, font, bright);
                        }
                    }
                    else display(current, window, font, bright);
                }
            }
        }
    }

    return 0;
}

int play(const string& username, game2048 resume) {
    stackh<game2048> stack(resume);
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + 100), "2048 Game");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return 0;
    }

    bool winner = stack.current().isWinning();
    display(stack.current(), window, font, bright);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                      


            nguyeenn 
                s



            bool (game2048:: * resive)();
            if (event.type == sf::Event::KeyPressed) {
                char ch;
                switch (event.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    stack.remove();
                    resive = &game2048::Left;
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    stack.remove();
                    resive = &game2048::Right;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    stack.remove();
                    resive = &game2048::Up;
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    stack.remove();
                    resive = &game2048::Down;
                    break;
                case sf::Keyboard::R:
                    if (!UnRedo) continue;
                    if (stack.go_back()) {
                        display(stack.current(), window, font, bright);
                    }
                    continue;
                case sf::Keyboard::U:
                    if (!UnRedo) continue;
                    if (stack.go_foward()) {
                        display(stack.current(), window, font, bright);
                    }
                    continue;
                case sf::Keyboard::E:
                    addInfo(Info{ username, SIZE, UnRedo, stack.current() });
                    return -1;
                case sf::Keyboard::Q:
                    return stack.current().score;
                default:
                    resive = &game2048::Inactive;
                    break;
                }

                game2048 current = stack.current();
                if (current.moving(resive)) {
                    stack.push_back(current);
                    if (current.isLosing()) {
                        display(current, window, font, bright);
                        sf::sleep(sf::seconds(1));
                        display(current, window, font, moody);
                        display(current, window, font, moody);

                        int undo = displayLosing(window, font, UnRedo);
                        if (undo == -1) {
                            window.close();
                            return play(username);
                        }
                        else if (undo == 0) {
                            window.close();
                            return stack.current().score;
                        }
                        else {
                            stack.go_foward();
                            display(stack.current(), window, font, bright);
                        }
                    }
                    else if (current.isWinning() && winner == false) {
                        winner = true;
                        display(current, window, font, bright);
                        sf::sleep(sf::seconds(1));
                        display(current, window, font, moody);
                        display(current, window, font, moody);
                        int winner = displayWinning(window, font);
                        if (winner == 0) {
                            window.close();
                            addInfo(Info{ username, SIZE, UnRedo, stack.current() });
                            return -1;
                        }
                        else {
                            display(current, window, font, bright);
                        }
                    }
                    else display(current, window, font, bright);
                }
            }
        }
    }

    return 0;
}
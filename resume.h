#ifndef RESUME
#define RESUME

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "vector.h"
#include "game2048.h"

struct Info {
    string username;
    int size;
    int canUndo;
    game2048 gameState;

    bool operator == (const Info& other) {
        return this->username == other.username;
    }
};

const Info EMPTY = Info{};

vectorh<Info> readDataResume();
void writeDataResume(const vectorh<Info>& data);
void addInfo(const Info& newInfo);
Info displayResume(vectorh<Info>& data);

#endif // !RESUME

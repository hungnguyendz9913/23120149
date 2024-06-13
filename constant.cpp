#include <iostream>
#include <random>
#include "constant.h"

using namespace std;

int SIZE = 4;
bool UnRedo = false;

int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max - 1);
    return dis(gen);
}


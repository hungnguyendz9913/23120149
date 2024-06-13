#ifndef TOPLIST
#define TOPLIST

#include <fstream>
#include <iostream>
#include <sstream>
#include "vector.h"
using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b);
void readTop20List(vectorh<pair<string, int> > &Tlist);
void writeTop20List(vectorh<pair<string, int> >& Tlist);
void displayTlist(vectorh<pair<string, int> > Tlist);

#endif // !TOPLIST

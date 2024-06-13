#include "topList.h"

bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

void readTop20List(vectorh<pair<string, int> > &Tlist) {
    Tlist.clear();
    ifstream inFile("Top_20_List.bin", ios::binary);
    if (!inFile.is_open()) {
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find('-');

        string username = line.substr(0, pos);
        int score;
        if (istringstream(line.substr(pos + 1)) >> score) {
            Tlist.push_back({ username, score });
        }
    }

    inFile.close();
}

void writeTop20List(vectorh<pair<string, int> >& Tlist) {
    Tlist.sort(cmp);
    while (Tlist.size() > 20) Tlist.pop_back();

    ofstream outFile("Top_20_List.bin", ios::binary);

    if (!outFile) {
        return;
    }

    for (const auto& item : Tlist) {
        string line = item.first + "-" + to_string(item.second);
        outFile.write(line.c_str(), line.size());
        outFile.put('\n');
    }

    outFile.close();
}
#include "menu.h"
#include <fstream>

void createData(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile) {
        return;
    }

    for (int i = 1; i <= 20; ++i) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "player name %02d-0", i);
        outFile.write(buffer, strlen(buffer));
        outFile.put('\n');
    }

    outFile.close();
}

void clearData(string filename) {
    std::ofstream file(filename, std::ios::trunc);
}

int main() {
 //   createData("Top_20_List.bin");
	//clearData("resume.bin");
	menu();
}
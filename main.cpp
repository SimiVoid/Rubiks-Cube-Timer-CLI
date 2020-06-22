#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <conio.h>

void timer(const int& mode);

int main(int argc, char* argv[]) {
    while(true) {
        system("clear");

        std::cout << " === Rubik's Cube Timer === \n\n";
        std::cout << " [1] - 2x2x2\n";
        std::cout << " [2] - 3x3x3\n\n";
        std::cout << " [x] - Close\n";

        switch(_getch()) {
            case '1':
                timer(2);
                break;
            case '2':
                timer(3);
                break;
            case 'x':
                exit(0);
                break;
        }
    }

    return 0;
}

void timer(const int& mode) {
    system("clear");

    std::cout << " === Rubik's Cube Timer === \n\n";
    std::cout << " ======== 00:00:00 ======== \n\n";
    std::cout << " Press space to start...\n";

    while(_getch() == ' ');

    std::chrono::duration<double> timeSplit{};
    auto start = std::chrono::high_resolution_clock::now();

    while(_getch() == ' ') {
        system("clear");

        timeSplit = std::chrono::high_resolution_clock::now() - start;

        auto ms = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(timeSplit).count() % 100);
        auto s = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(timeSplit).count() % 60);
        auto m = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(timeSplit).count());

        if (ms.length() == 1)  ms = "0" + ms;
        if (m.length() == 1)  m = "0" + m;
        if (s.length() == 1)  s = "0" + s;

        std::string timeString = m + ':' + s + ':' + ms;

        std::cout << " === Rubik's Cube Timer === \n\n";
        std::cout << " ======== " << timeString << " ======== \n\n";
    }
}
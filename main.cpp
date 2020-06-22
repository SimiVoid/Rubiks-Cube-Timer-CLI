#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <windows.h>

std::map<int, std::vector<std::chrono::duration<double>>> results;

void timer(const int& mode);
void loadResults();
void saveResults();

int main(int argc, char* argv[]) {
    loadResults();

    while(true)
    {
        system("cls");

        std::cout << " === Rubik's Cube Timer === \n\n";
        std::cout << " [1] - 2x2x2\n";
        std::cout << " [2] - 3x3x3\n";
        std::cout << " [3] - 4x4x4\n";
        std::cout << " \n";
        std::cout << " [x] - Close\n";

        while(true) {
            if (GetAsyncKeyState('1') & 0x8000) {
                timer(2);
                break;
            }
            else if (GetAsyncKeyState('2') & 0x8000) {
                timer(3);
                break;
            }
            else if (GetAsyncKeyState('3') & 0x8000) {
                timer(4);
                break;
            }
            else if (GetAsyncKeyState('x') & 0x8000)
                exit(0);
        }
    }
}

std::string resultToString(const std::chrono::duration<double>& result) {
    auto ms = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(result).count() % 100);
    auto s = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(result).count() % 60);
    auto m = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(result).count());

    if (ms.length() == 1)  ms = "0" + ms;
    if (m.length() == 1)  m = "0" + m;
    if (s.length() == 1)  s = "0" + s;

    return m + ':' + s + ':' + ms;
}

void timer(const int& mode) {
    system("cls");

    std::cout << " === Rubik's Cube Timer === \n\n";
    std::cout << " ======== 00:00:00 ======== \n\n";
    std::cout << " Press space to start...\n";

    while(!(GetAsyncKeyState(VK_SPACE) & 0x8000));
    while(GetAsyncKeyState(VK_SPACE) & 0x8000);

    std::chrono::duration<double> timeSplit{};
    auto start = std::chrono::high_resolution_clock::now();

    while(!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        system("cls");

        timeSplit = std::chrono::high_resolution_clock::now() - start;

        std::cout << " === Rubik's Cube Timer === \n\n";
        std::cout << " ======== " << resultToString(timeSplit) << " ======== \n\n";
        std::cout << " Press space to end...\n";
    }

    std::cout << " === Rubik's Cube Timer === \n\n";
    std::cout << " ======== " << resultToString(timeSplit) << " ======== \n\n";
    std::cout << " Best:  " << resultToString(*std::min_element(results[mode].begin(), results[mode].end())) << "\n";
    std::cout << " Avg5:  " << "\n";
    std::cout << " Avg12: " << "\n";
}

void loadResults() {
    auto path = std::string(getenv("APPDATA")) + "\\SimiVoid\\Timer";

    if(!std::filesystem::is_directory(path))
        return;

    for(auto& file : std::filesystem::recursive_directory_iterator(path)) {
        if(file.path().extension() == ".dat") {
            std::ifstream inputFile(file);
            double line;

            if(inputFile.is_open() && inputFile.good())
                while(inputFile >> line)
                    results[file.path().string()[file.path().string().length() - 5] - 48].emplace_back(std::chrono::duration<double>(line));
        }
    }
}

void saveResults() {
    auto path = std::string(getenv("APPDATA")) + "\\SimiVoid\\Timer";

    if(!std::filesystem::is_directory(path))
        std::filesystem::create_directories(path);

    for(auto e : results) {
        std::ofstream outputFile(path + "\\" + std::to_string(e.first) + ".dat");

        for(auto r : e.second)
            outputFile << r.count() << "\n";
    }
}
#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

const int rows = 5;
const int cols = 5;
const int gridSize = rows * cols;
const string baseFileName = "cards";
int cardnumber;

void shuffleArray(int* arr, int size) {
    random_shuffle(arr, arr + size);
}

int gen() {
    srand(static_cast<unsigned>(time(0)));

    if (!fs::exists("Cards")) {
        fs::create_directory("Cards");
    }

    cout << "How many cards do you want to create?";
    cin >> cardnumber;
    system("clear");
    int numbers[gridSize];
    for (int i = 0; i < gridSize; ++i) {
        numbers[i] = i + 1;
    }

    for (int i = 1; i <= cardnumber; ++i) {
        shuffleArray(numbers, gridSize);

        stringstream fileNameStream;
        fileNameStream << "Cards" << "/" << baseFileName << "_" << i << ".txt";
        string fileName = fileNameStream.str();

        ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int j = 0; j < gridSize; ++j) {
                outputFile << numbers[j] << " ";
                if ((j + 1) % cols == 0) { 
                    outputFile << endl; 
                }
            }

            outputFile.close();
        }
    }

    cout << "Your" << cardnumber << " cards have been generated in the Cards folder.\n";

}

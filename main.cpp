#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <algorithm>
namespace fs = std::filesystem;
using namespace std;

string blue = "\u001b[34m";
string red = "\u001b[31m";
string reset = "\u001b[0m";
string bold = "\u001b[1m";

#define NUMEROS 100
#define COLUNAS 10
#define DELAY 1000000

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


void clearScreen()
{
    cout << "\033[2J\033[1;1H" << flush;
}

int geraNumero(int maxNumber)
{
    return rand() % maxNumber + 1;
}

void mainmenu()
{
    cout << blue << bold << "E S C O L H A    A    O P Ç Â O: \n"
         << reset
         << blue << "--------------------------\n"
         << "1 - Sorteio Automático\n"
         << "2 - Sorteio Manual\n"
         << "3 - Gerar Cartões\n"
         << "4 - Sair\n"
         << "--------------------------\n"
         << bold << "O P Ç Ã O: "
         << reset;
}

void displayNumber(int number, const string &color, const string &label)
{
    cout << color << label << ": " << number << reset << endl;
}

void displayPanel(int pickedAmount, int currentNumber, int sortedNumbers[], int sortedCount)
{
    cout << "Picked Amount: " << pickedAmount << "\n";
    cout << "Panel:\n";

    for (int i = 1; i <= pickedAmount; i++)
    {
        bool isSorted = find(sortedNumbers, sortedNumbers + sortedCount, i) != sortedNumbers + sortedCount;

        if (isSorted)
        {
            cout << red << setw(5) << i;
        }
        else
        {
            cout << blue << setw(5) << i;
        }

        if (i % COLUNAS == 0)
        {
            cout << endl;
        }
        else
        {
            cout << "\t";
        }
    }

    if (pickedAmount % COLUNAS != 0)
    {
        cout << endl;
    }
}

int main()
{
    srand(time(NULL)); // Seed for random number generation

    int bingotype;
    int quantity;
    int previousNumber = 0;
    int currentNumber = 0;
    int sortedNumbers[NUMEROS] = {0};
    int sortedCount = 0;

    do
    {
        clearScreen();
        mainmenu();
        cin >> bingotype;

        if (bingotype == 1 || bingotype == 2)
        {
            clearScreen();
            cout << (bingotype == 1 ? "You selected 'Automatic Draw'" : "You selected 'Manual Draw'") << endl;
            cout << "Enter the quantity of numbers for the draw (75, 90, 100): ";
            cin >> quantity;
            cin.ignore(); // Clear buffer after reading number

            if ((quantity == 75) || (quantity == 90) || (quantity == 100))
            {
                sortedCount = 0;
                fill_n(sortedNumbers, NUMEROS, 0);

                while (sortedCount < quantity)
                {
                    if (bingotype == 2)
                    {
                        cout << "Press Enter to draw a number...";
                        cin.get(); // Wait for Enter key press for manual draw
                    }

                    clearScreen();
                    displayNumber(previousNumber, red, "Previous Number");

                    do {
                        currentNumber = geraNumero(quantity);
                    } while (find(sortedNumbers, sortedNumbers + sortedCount, currentNumber) != sortedNumbers + sortedCount);

                    displayNumber(currentNumber, blue, "Current Number");
                    displayPanel(quantity, currentNumber, sortedNumbers, sortedCount);

                    previousNumber = currentNumber;
                    sortedNumbers[sortedCount++] = currentNumber;

                    if (bingotype == 1)
                    {
                        usleep(DELAY); // Delay for automatic draw
                    }
                }

                cout << (bingotype == 1 ? "Automatic" : "Manual") << " draw complete. Press Enter to continue...";
                cin.get();
                clearScreen();
            }
            else
            {
                cout << "Invalid input. The number must be 75, 90, or 100." << endl;
            }
        }
        else if (bingotype == 3)
        {
            cout << "You selected 'Generate Cards'" << endl;
            gen();
        }
        else if (bingotype == 4)
        {
            cout << "Exiting..." << endl;
            break;
        }
        else
        {
            cout << "Invalid Answer, try again or press '4' to quit" << endl;
        }
    } while (true);

    return 0;
}
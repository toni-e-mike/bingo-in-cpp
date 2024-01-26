#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
using namespace std;

string blue = "\u001b[34m";
string red = "\u001b[31m";
string reset = "\u001b[0m";
string bold = "\u001b[1m";

#define NUMEROS 100
#define COLUNAS 10
#define DELAY 1000000
#define MODO_AUTO false

void clearScreen()
{
    cout << "\033[2J\033[1;1H" << flush;
}

int geraNumero()
{
    return rand() % NUMEROS + 1;
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

    int totalNumbersToDisplay = min(pickedAmount, NUMEROS);

    for (int i = 1; i <= totalNumbersToDisplay; i++)
    {
        bool isCurrent = (i == currentNumber);
        bool isSorted = false;

        for (int j = 0; j < sortedCount; j++)
        {
            if (sortedNumbers[j] == i)
            {
                isSorted = true;
                break;
            }
        }

        if (isCurrent)
        {
            cout << blue << setw(5) << i;
        }
        else if (isSorted)
        {
            cout << red << setw(5) << i;
        }
        else
        {
            cout << blue << setw(5) << i;
        }

        if (i % COLUNAS == 0)
        {
            cout << reset << endl;
        }
        else
        {
            cout << "\t";
        }
    }

    if (totalNumbersToDisplay % COLUNAS != 0)
    {
        cout << reset << endl;
    }
}

int main()
{
    int bingotype;
    int quantity;
    int previousNumber = 0;
    int currentNumber = 0;
    const int MAX_PREVIOUS = 5;
    int previousNumbers[MAX_PREVIOUS];

    do
    {
        clearScreen();
        mainmenu();
        cin >> bingotype;

        if (bingotype == 1)
        {
            clearScreen();
            cout << "You selected 'Automatic Draw'" << endl;
            cout << "Enter the quantity of numbers for the draw (75, 90, 100): ";
            cin >> quantity;

            if ((quantity == 75) || (quantity == 90) || (quantity == 100))
            {
                cout << "You entered one of the allowed numbers." << endl;

                int sortedNumbers[NUMEROS];
                int sortedCount = 0;

                for (int i = 0; i < MAX_PREVIOUS; i++)
                {
                    previousNumbers[i] = 0;
                }

                for (int i = 0; i < quantity && sortedCount < quantity; i++)
                {
                    clearScreen();

                    // Display previous number in red
                    displayNumber(previousNumber, red, "Previous Number");

                    // Draw a new number
                    currentNumber = geraNumero();

                    // Display current number in blue
                    displayNumber(currentNumber, blue, "Current Number");

                    // Display panel with columns
                    displayPanel(quantity, currentNumber, sortedNumbers, sortedCount);

                    // Update previousNumber with the drawn number
                    previousNumber = currentNumber;

                    // Update sortedNumbers with the currentNumber
                    sortedNumbers[sortedCount++] = currentNumber;

                    usleep(DELAY); // Add delay before drawing the next number
                }

                // Clear the screen after displaying all the numbers
                cout << "Press Enter to continue...";
                cin.ignore(); // Wait for Enter key press
                clearScreen();
            }
            else
            {
                cout << "Invalid input. The number must be 75, 90, or 100." << endl;
            }
        }
        else if (bingotype == 2)
        {
            cout << "You selected 'Manual Draw'" << endl;
        }
        else if (bingotype == 3)
        {
            cout << "You selected 'Generate Cards'" << endl;
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

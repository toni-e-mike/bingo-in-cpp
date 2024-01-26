#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Here you can change the settings of the game 

#define Numbers 10 // the most common numbers are 75/90/100
#define Columns 5
#define Delay 1000000

// This is going to generate a random number

int geneNumber() {
    return rand() % Numbers + 1;
}

// This is going to create the numbers for the bingo game

void createNumbers(int number[]) {
    int x = 0, y = 0, aux = 0;
    bool repeat;

    while(x < Numbers) {
        aux = geneNumber();
        repeat = false;
        for(y = 0; y < x; y++) {
            if(aux == number[y]) {
                repeat = true;
                break;
            }
        }
        if(!repeat) {
            number[x] = aux;
            x++;
        }
    }
}

int main(){
    char answer;
    srand(time(0)); // This is going to initialize a random seed

    cout << "Welcome to the bingo game" << endl;
    cout << "The sortition is comprised between 1 and " << Numbers << endl;
    cout << "Would you like to continue?" <<endl;
    cout << "[Y] To continue, [N] To stop: ";

do{
    char answer;
    
    cin >> answer;
    if(answer == 'N'||answer == 'n') {
        return 0;
    }else if (answer == 'Y' || answer == 'y'){
        break;
    }else{
        cout<< "Invalid Input" <<endl;
        cout<< "Try again (Y/N): " ;
        
     }
}while(true);
    

    do {
        system("clear");
        int number[Numbers];
        createNumbers(number);
        char answer;

        // This will display the generated numbers with a delay that we set at the start of the code
        
        for(int x = 0; x < Numbers; x++) {
            cout << number[x] << "\t";
            usleep(Delay);

            if((x + 1) % Columns == 0) {
                cout << endl;
            }
        }
        
        // Ask if user would like to play again
        
        cout << "Would you like to generate a new bingo game? (Y/N): ";
        cin >> answer;
        if(answer == 'Y' || answer == 'y') {
            return 0;
        }else if(answer == 'N'||answer == 'n') {
           break; cout<< "Thank you for playing";

       
    } 
}while(true);


return 0;

}

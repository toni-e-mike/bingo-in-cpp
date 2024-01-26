#include <iostream>
#include <unistd.h>
#include "cardgen.h"

int NUMEROS;
int choice;
#define COLUNAS     10
#define DELAY       1000000 //1 segundo
#define MODO_AUTO   false

using namespace std;



int geraNumero(){
    return rand() % NUMEROS + 1;
}


void geraChave(int chave[]){
    int i = 0, j = 0, aux = 0;
    bool existent = false;
    while(i < NUMEROS){
        aux = geraNumero();
        for(j = 0; j < i; j++){
            if(aux == chave[j]){
                existent = true;
                break;
            }
        }
        if(!existent){
            chave[i] = aux;
            i++;
        }
        existent = false;
    }
}


void ordenaChave(int chave[]){
    int aux = 0;
    for(int i = 0; i < NUMEROS; i++){
        for(int j = i + 1; j < NUMEROS; j++){
            if(chave[i] > chave[j]){
                aux = chave[i];
                chave[i] = chave[j];
                chave[j] = aux;
            }
        }
    }
}


int main(){


    int resposta;
    int ctrl = 0;

    do{
        system("clear");
        cout << "Bem vindo ao bingo!" << endl;
        cout << "1) Jogar\n2) Gerar cartões\n3) Sair\n\n";

       cin >> resposta; 

       switch(resposta){
       case 3:
           break;
        case 2:
            gen();
        case 1:
            do{
        
        system("clear");
        int chave[NUMEROS];
        geraChave(chave);
        cout << "Quantos numeros queres sortear?\n1)75\n2)90\n3)100\n";
        cin >> choice;

        switch (choice) {
        case 1:
            NUMEROS = 75;
            break;
        case 2:
            NUMEROS = 90;
            break;
        case 3:
            NUMEROS = 100;
            break;
    }
        cout << "Números Sorteados ==============================================" << endl;
        for(int i = 0; i < NUMEROS; i++){
            
            cout << chave[i];
            usleep(DELAY);
            cout << "\t" << flush; 
            if((i + 1) % COLUNAS == 0){
                cout << endl;
            }
        }
        cout << endl;
        cout << "Todos os numeros foram sorteados.\nJogar novamente? (s/n) ";
        cin >> resposta;
    }while(resposta == 's');
    
    return 0;

       default:
           cout << "Opção inválida" << endl;
           usleep(DELAY);
       }
    }while(true);
    
    
    }
      

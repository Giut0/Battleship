/*
 ============================================================================
 Name        : Battleship
 Author      : Vito Proscia
 Version     : 1.0
 Description : Simplification of the naval battle game
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROW 6
#define MAX_COLUMN 6
#define MAX_SHIPS 6
#define MAX_ATTEMPTS 10
#define SHIP_CODE 88 //ASCII code of the 'X', with which ships are marked
#define ASCII_CODE_A 65
#define SINKED_SHIP_CODE 67 //ASCII code of 'C' with which sunken ships are marked
#define EMPTY_CELL_CODE 48 //ASCII code of '0' with which empty cell are marked

void initializeTable(char table[MAX_ROW][MAX_COLUMN]); //Initialize table with '0' at all cells
void showTable(char table[MAX_ROW][MAX_COLUMN]);
void spawnShips(char table[MAX_ROW][MAX_COLUMN]); //Spawn ships in random cells
unsigned short isCorrectInput(unsigned short column, unsigned short row, unsigned short inputNumber); //Checking for correctness of input

int main(void) {

    srand(time(NULL));

    char battleshipTable[MAX_ROW][MAX_COLUMN]; //Char matrix to optimize memory space
    char battleshipGameTable[MAX_ROW][MAX_COLUMN]; //Char matrix showed in game
    char currentColumn;
    unsigned short currentRow = 0, NumberCurrentColumn = 0, score = 0, inputNumber = 0, flagCorrectInput = 0;

    printf("\n************************* Battaglia navale *************************\n\n");
    printf("Benvenut* gamer, ho posizionato casualmente delle navi in una tabella, vediamo se riesci a trovarle tutte 😇 \n\n");
    printf(" 📜 Regole principali: \n"
           " 1) Inserisci una coppia di valori es. A1 oppure b4, dove alle lettere corrispondono le colonne mentre ai numeri corrispondono le righe; \n"
           " 2) Le colonne vanno dalla A alla F (si possono inserire anche lettere minuscole) e le righe vanno da 1 a 6; \n"
           " 3) Hai a disposizione 10 tentativi per trovare tutte le navi che ho sistemato; \n"
           " 4) Divertiti!! \n \n");

    printf("Ti tengo d'occhio, non barare 👀 \n \n");
    printf("************************* Iniziamo ************************* \n\n");
    printf("Per aiutarti ti mostro la tabella vuota: \n \n");

    initializeTable(battleshipTable);
    initializeTable(battleshipGameTable); 

    showTable(battleshipTable);

    spawnShips(battleshipTable);

    for(int i = 0; i < MAX_ATTEMPTS; i++){

        do{
            flagCorrectInput = 0;
            printf("\nInserire la %da mossa (nel formato colonna riga es. A5 oppure b4): ", (i + 1));
            inputNumber = scanf("%c%hu", &currentColumn, &currentRow);

            //Subtracts the ASCII code of the entered letter from the ASCII code of the letter A to make the input corresponsive to numbers >= 0
            NumberCurrentColumn = toupper(currentColumn) - ASCII_CODE_A;

            if(isCorrectInput(NumberCurrentColumn, currentRow, inputNumber)){
                printf("\n⛔ Input non corretto, si prega di inserire valori che per le righe vanno da 1 a 6 e per le colonne le lettere dalla A alla F ⛔\n");
                flagCorrectInput = 1;
            }

        }while(flagCorrectInput == 1); 

        if(battleshipTable[currentRow - 1][NumberCurrentColumn] == SHIP_CODE){

            printf("🥳 Nave colpita \n\n");
            score++;

            //Replaces the ship carattetre 'X' with another 'C' so as not to cover the same ship
            battleshipTable[currentRow - 1][NumberCurrentColumn] = 'C';
            battleshipGameTable[currentRow - 1][NumberCurrentColumn] = 'C';

            showTable(battleshipGameTable);

            if(score == MAX_SHIPS){  //End game in case all ships are sunk

                i = MAX_ATTEMPTS;
            }

        }else if(battleshipTable[currentRow - 1][NumberCurrentColumn] == EMPTY_CELL_CODE){

            printf("🥲  Nave mancata, ritenta! \n\n");
            battleshipGameTable[currentRow - 1][NumberCurrentColumn] = '*';
            showTable(battleshipGameTable);

        }else if(battleshipTable[currentRow - 1][NumberCurrentColumn] == SINKED_SHIP_CODE){

            printf("😑 Nave già affondata, inserire un input diverso! \n\n");
            i--;
            showTable(battleshipGameTable);
        }

    }

    printf("\n************************* Partita Terminata *************************\n\n");

    if(score == MAX_ATTEMPTS){

        printf("🎉 CONGRATULAZIONI HAI OTTENUTO IL MASSIMO DEL PUNTEGGIO: %d 🎉", score);
    }

    printf("Punteggio: %d \n\n", score);

    printf("Per onor del vero ecco a te la tabella con le navi \n\n");

    showTable(battleshipTable);

    printf("\nLegenda: \n"
           "- Con X vengono indicate le navi che non hai affondato; \n"
           "- Con C vengono indicate le navi che hai affondato; \n"
           "- Con 0 vengono indicate le caselle vuote. \n\n");

    return 0;
}

void initializeTable(char table[MAX_ROW][MAX_COLUMN]){

    for(int i = 0; i < MAX_ROW; i++){

        for(int j = 0; j < MAX_COLUMN; j++){

            table[i][j] = '0';
        }

    }
}

void showTable(char table[MAX_ROW][MAX_COLUMN]){

    puts("   |  A   B   C   D   E   F ");
    puts("---+------------------------");

    for(int i = 0; i < MAX_ROW; i++){

        printf(" %hu |", (i + 1));

        for(int j = 0; j < MAX_COLUMN; j++){

            printf("  %c ", table[i][j]);
        }

        printf("\n");
    }
}

void spawnShips(char table[MAX_ROW][MAX_COLUMN]){

    unsigned short randRow, randColumn;

    for(int i = 0; i <= MAX_SHIPS; i++){

        randRow = rand() % MAX_ROW;
        randColumn = rand() % MAX_COLUMN;

        table[randRow][randColumn] = 'X';
    }
}

unsigned short isCorrectInput(unsigned short column, unsigned short row, unsigned short inputNumber){

    unsigned short flagCorrectInput = 0;

    while(getchar() != '\n'); //Removes any characters left in the buffer up to the newline

    if((column < 0 || column > MAX_COLUMN) || (row < 0 || row > MAX_ROW) || (inputNumber != 2)){
        flagCorrectInput = 1;
    }

    return flagCorrectInput;
}
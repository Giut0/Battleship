/*
 ============================================================================
 Name        : Battleship.c
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
#define SHIP_CODE 88 //ASCII code of the X, with which ships are marked
#define ASCII_CODE_A 65
#define SINKED_SHIP_CODE 67 //ASCII code of C with which sunken ships are marked
#define CODICE_CASELLA_VUOTA 48 //ASCII code of 0 with which empty boxes are marked

void initialize_Table(char table[MAX_ROW][MAX_COLUMN]);
void outputTable(char table[MAX_ROW][MAX_COLUMN]);
void spawnsShips(char table[MAX_ROW][MAX_COLUMN]);
unsigned short isCorrectInput(unsigned short column, unsigned short row, unsigned short inputNumber);

//TODO: Funzione che mostra la griglia di gioco con '*' per le casella dove è stato fatto un buco nell'acqua, 'X' per le navi colpite

int main(void) {

    srand(time(NULL));

    char battleshipTable[MAX_ROW][MAX_COLUMN]; //Matrice di char per ottimizzare lo spazio in memoria
    char currentColumn;
    unsigned short currentRow = 0, NumberCurrentColumn = 0, score = 0, inputNumber = 0, i = 0;

    printf("\n************************* Battaglia navale *************************\n\n");
    printf("Benvenut* gamer, ho posizionato casualmente delle navi in una tabella, vediamo se riesci a trovarle tutte (◠‿◠) \n \n");
    printf("Regole principali: \n"
           " 1) Inserisci una coppia di valori es. A1 oppure b4, dove alle lettere corrispondono le colonne mentre ai numeri corrispondono le righe; \n "
           "2) Le colonne vanno dalla A alla F (si possono inserire anche lettere minuscole) e le righe vanno da 1 a 6; \n"
           " 3) Hai a disposizione 10 tentativi per trovare tutte le navi che ho sistemato; \n"
           " 4) Divertiti!! \n \n");

    printf("Ti tengo d'occhio, non barare ಠ_ಠ \n \n");
    printf("************************* Iniziamo ************************* \n\n");

    printf("Per aiutarti ti mostro la tabella vuota: \n \n");

    initialize_Table(battleshipTable);
    outputTable(battleshipTable);

    spawnsShips(battleshipTable);

    for(i = 0; i < MAX_ATTEMPTS; i++){

        do{
            printf("\nInserire la %da mossa (nel formato colonna riga es. A5 oppure b4): ", (i + 1));
            inputNumber = scanf("%c%hu", &currentColumn, &currentRow);

            //Sottrae al codice ASCII della lettera inserita il codice ASCII della lettera A per far corispondere l'input a numeri >= 0
            NumberCurrentColumn = toupper(currentColumn) - ASCII_CODE_A;

        }while(isCorrectInput(NumberCurrentColumn, currentRow, inputNumber)); //Controllo della correttezza dell'input

        if(battleshipTable[currentRow - 1][NumberCurrentColumn] == SHIP_CODE){

            printf("Nave colpita \n");
            score++;

            //Sostituisce il carattetre della nave 'X' con un altro 'C' per non coplire la stessa nave
            battleshipTable[currentRow - 1][NumberCurrentColumn] = 'C';

            if(score == MAX_SHIPS){  //Fine gioco in caso vengano affondate tutte le navi

                i = MAX_ATTEMPTS;
            }

        }else if(battleshipTable[currentRow - 1][NumberCurrentColumn] == CODICE_CASELLA_VUOTA){

            printf("Nave mancata, ritenta! \n");

        }else if(battleshipTable[currentRow - 1][NumberCurrentColumn] == SINKED_SHIP_CODE){

            printf("Nave già affondata, inserire un input diverso! \n");
            i--;
        }

    }

    printf("\n************************* Partita Terminata *************************\n\n");

    if(score == MAX_ATTEMPTS){

        printf("CONGRATULAZIONI HAI OTTENUTO IL MASSIMO DEL PUNTEGGIO: %d", score);
    }

    printf("Punteggio: %d \n\n", score);

    printf("Per onor del vero ecco a te la tabella con le navi \n\n");

    outputTable(battleshipTable);

    printf("\nLegenda: \n"
           "- Con X vengono indicate le navi che non hai affondato; \n"
           "- Con C vengono indicate le navi che hai affondato; \n"
           "- Con 0 vengono indicate le caselle vuote. \n");

    return 0;
}

void initialize_Table(char table[MAX_ROW][MAX_COLUMN]){

    unsigned short i, j;

    for(i = 0; i < MAX_ROW; i++){

        for(j = 0; j < MAX_COLUMN; j++){

            table[i][j] = '0';
        }

    }
}

void outputTable(char table[MAX_ROW][MAX_COLUMN]){

    unsigned short i, j;

    puts("   |  A   B   C   D   E   F ");
    puts("---+------------------------");

    for(i = 0; i < MAX_ROW; i++){

        printf(" %hu |", (i + 1));

        for(j = 0; j < MAX_COLUMN; j++){

            printf("  %c ", table[i][j]);
        }

        printf("\n");
    }
}

void spawnsShips(char table[MAX_ROW][MAX_COLUMN]){

    unsigned short randRighe, randColonne, i;

    for(i = 0; i <= MAX_SHIPS; i++){

        randRighe = rand() % MAX_ROW;
        randColonne = rand() % MAX_COLUMN;

        table[randRighe][randColonne] = 'X';
    }
}

unsigned short isCorrectInput(unsigned short column, unsigned short row, unsigned short inputNumber){

    unsigned short flagInputCorretto = 0;

    while(getchar() != '\n'); //Rimuove eventuali caratteri rimasti nel buffer fino al newline

    if((column < 0 || column > MAX_COLUMN) || (row < 0 || row > MAX_ROW) || (inputNumber != 2)){

        flagInputCorretto = 1;
        printf("!!! Input non corretto, si prega di inserire valori che per le righe vanno da 1 a 6 e per le colonne le lettere dalla A alla F !!!\n");
    }

    return flagInputCorretto;
}

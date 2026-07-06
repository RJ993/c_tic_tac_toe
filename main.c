#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char *name;
    char symbol;
}Player;

void boardPrinter(char *boardSpots);
void checkWinner(Player player, char *boardSpots, bool *pGameConcluded);
void playerTurn(Player player, char *boardSpots, bool *pGameConcluded);
void play(Player first, Player second);
void getName(char symbol, Player *pPlayer);

int main(void){
    char first = '\0';
    Player xPlayer = {"", 'X'};
    Player oPlayer = {"", 'O'};

    printf("}---- TIC-TAC-TOE ----{\n\n");

    getName('X', &xPlayer);

    if (xPlayer.name == NULL) {
        return 1;
    }

    getName('O', &oPlayer);

    if (oPlayer.name == NULL) {
        return 1;
    }

    do{
        printf("Who goes first, X or O?: ");
        first = getchar();
    }while(first != 'X' && first != 'O');

    (first == 'X') ? play(xPlayer, oPlayer) : play(oPlayer, xPlayer);
    free(xPlayer.name);
    free(oPlayer.name);
    xPlayer.name = NULL;
    oPlayer.name = NULL;

    return 0;
}

void boardPrinter(char *boardSpots){
    for (int i = 0; i < 9; i++){
        (boardSpots[i] == '\0') ? printf("   ") : printf(" %c ", boardSpots[i]);
        if (i % 3 != 2) printf("|");
        if (i % 3 == 2 && i < 8) printf("\n-----------\n");
    }
    printf("\n\n");
}
void checkWinner(Player player, char *boardSpots, bool *pGameConcluded){
    // A way to resolve ties could be tracking squares occupied and then if all 9 are filled with no winner, tie.

    const int winningCombos[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6},
    };

    for (int comboIn = 0; comboIn < 8; comboIn++){
        if (!(*pGameConcluded)) {
            bool everySpot = true;
            for (int spotIn = 0; spotIn < 3; spotIn++){
                if (boardSpots[winningCombos[comboIn][spotIn]] != player.symbol) everySpot = false;
            }
            if (everySpot) {
                (*pGameConcluded) = true;
                printf("%s has won!\n", player.name);
            }
        }
    }
}
void playerTurn(Player player, char *boardSpots, bool *pGameConcluded){
    int chosenSpot = 0;
    do {
        printf("Which spot, %s? (1-9): ", player.name);
        scanf("%i", &chosenSpot); 
        getchar();
    }while ((chosenSpot < 1 && chosenSpot > 9) || boardSpots[chosenSpot - 1] != '\0');
    boardSpots[chosenSpot - 1] = player.symbol;
    boardPrinter(boardSpots);
    checkWinner(player, boardSpots, pGameConcluded);
}
void play(Player first, Player second){
    char boardSpots[9] = {"\0"};
    bool gameConcluded = false;
    do{
        playerTurn(first, boardSpots, &gameConcluded);
        if (!gameConcluded){ playerTurn(second, boardSpots, &gameConcluded);}
    }while(!gameConcluded);
}
void getName(char symbol, Player *pPlayer){
    char nameVar[31] = "";
    do{
        printf("Who will play with the %cs (30 characters maximum)?: ", symbol);
        fgets(nameVar, sizeof(nameVar), stdin);
        nameVar[strlen(nameVar) - 1] = '\0';
    }while(strlen(nameVar) == 0);
    pPlayer->name = strndup(nameVar, sizeof(nameVar)); // strndup DYNAMICALLY allocates memory so it should be freed.
}
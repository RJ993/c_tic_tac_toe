#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char *name;
    char symbol;
}Player;

void boardPrinter(char *boardSpots);
void checkWinner(bool *pGameConcluded);
void playerTurn(Player player, char *boardSpots, bool *pGameConcluded);
void play(Player first, Player second);
void getName(char symbol, Player *pPlayer);

int main(void){
    char first = '\0';
    Player xPlayer = {"", 'X'};
    Player oPlayer = {"", 'O'};

    printf("}---- TIC-TAC-TOE ----{\n");

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
    
}
void checkWinner(bool *pGameConcluded){

}
void playerTurn(Player player, char *boardSpots, bool *pGameConcluded){
    int chosenSpot = 0;
    do {
        printf("Which spot, %s? (1-9): ", player.name);
        scanf("%d", &chosenSpot); 
    }while ((chosenSpot < 1 && chosenSpot > 9) && boardSpots[chosenSpot - 1] != "");
    boardSpots[chosenSpot - 1] = player.symbol;
    boardPrinter(boardSpots);
    checkWinner(pGameConcluded);
}
void play(Player first, Player second){
    char boardSpots[9] = {""};
    bool gameConcluded = true;
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
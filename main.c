#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char *name;
    char symbol;
}Player;

void boardPrinter();
void checkWinner(bool *gameConcluded);
void playerTurn(bool *gameConcluded);
void play(Player first, Player second, char *boardSpots);
void getName(char symbol, char *tmp);

int main(void){
    char boardSpots[9] = {""};
    char tmp[] = "";

    printf("}---- TIC-TAC-TOE ----{\n");

    getName('X', tmp);
    Player xPlayer = {tmp, 'X'};
    getName('O', tmp);
    Player oPlayer = {tmp, 'O'};

    do{
        printf("Who goes first, X or O?: ");
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strlen(tmp) - 1] = '\0';
    }while(strcmp(tmp, "X") != 0 && strcmp(tmp, "O") != 0);

    printf("%s", xPlayer.name);
    printf("%s", oPlayer.name);
    printf("%s", tmp);
   // (strcmp(tmp, "X") == 0) ? play(xPlayer, oPlayer, boardSpots) : play(oPlayer, xPlayer, boardSpots);

    return 0;
}

void boardPrinter(){

}
void checkWinner(bool *gameConcluded){

}
void playerTurn(bool *gameConcluded){
    boardPrinter();
    checkWinner(gameConcluded);
}
void play(Player first, Player second, char *boardSpots){
    bool gameConcluded = false;
    do{
        playerTurn(&gameConcluded);
        if (!gameConcluded){ playerTurn(&gameConcluded);}
    }while(!gameConcluded);
}
void getName(char symbol, char *tmp){
    do{
        printf("Who will play with the %cs (30 characters maximum)?: ", symbol);
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strlen(tmp) - 1] = '\0';
    }while(strlen(tmp) > 30);
}
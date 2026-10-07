#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define CON_FLAG 0x0
#define WIN_CON_FLAG 0x1
#define TIE_CON_FLAG 0x2

typedef struct{
    char *name;
    char symbol;
    u_int32_t flag;
}Player;

void boardPrinter(Player *pPlayer, Player *pOpponent);
void checkConditionState(u_int32_t playerFlag, u_int32_t board, u_int32_t *pGameConcluded);
void endOfTurn(char *name, u_int32_t gameConcluded);
void playerTurn(Player *player, Player *opponent, u_int32_t *pGameConcluded);
void play(Player *pFirst, Player *pSecond);
void getName(char symbol, Player *pPlayer);

int main(void){
    char first = '\0';
    int charBuffer = '\0';
    Player xPlayer = {"", 'X', 0b000000000};
    Player oPlayer = {"", 'O', 0b000000000};

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
        if (first != '\n') {
            while ((charBuffer = getchar()) != '\n' && charBuffer != EOF);
        }
    }while(first != 'X' && first != 'O');

    (first == 'X') ? play(&xPlayer, &oPlayer) : play(&oPlayer, &xPlayer);
    free(xPlayer.name);
    free(oPlayer.name);
    xPlayer.name = NULL;
    oPlayer.name = NULL;

    return 0;
}


void boardPrinter(Player *pPlayer, Player *pOpponent){
    u_int32_t board = pPlayer->flag | pOpponent->flag;
    for (int i = 0; i < 9; i++){
        u_int32_t boardPosition = 1 << i;

        if (board & boardPosition){
            if (pPlayer->flag & boardPosition) {
                printf(" %c ", pPlayer->symbol);
            }else{
                printf(" %c ", pOpponent->symbol);
            }
        }else{
            printf("   ");
        }

        if (i % 3 != 2) printf("|");
        if (i % 3 == 2 && i < 8) printf("\n-----------\n");
    }
    printf("\n\n");
}
void checkConditionState(u_int32_t playerFlag, u_int32_t board, u_int32_t *pGameConcluded){
    const u_int32_t winningCombos[8] = {
        0b000000111,
        0b000111000,
        0b111000000,
        0b001001001,
        0b010010010,
        0b100100100,
        0b100010001,
        0b001010100
    };

    const u_int32_t tieCondition = 0b111111111;

    for (int comboIn = 0; comboIn < 8; comboIn++){
        if ((playerFlag & winningCombos[comboIn]) == winningCombos[comboIn]) {
            (*pGameConcluded) = 0x1;
            return;
        }
    }

    if ((board & tieCondition) == tieCondition) (*pGameConcluded) = 0x2;
}
void endOfTurn(char *name, u_int32_t gameConcluded){ 
    switch(gameConcluded){
        case WIN_CON_FLAG:
            printf("%s has won!\n", name);
            break;
        case TIE_CON_FLAG:
            printf("Tie!\n");
            break;
    }
}
// (pPlayer->flag | pOpponent->flag) represents the board.
void playerTurn(Player *pPlayer, Player *pOpponent, u_int32_t *pGameConcluded){
    int chosenSpot = 0;
    do {
        printf("Which spot, %s? (1-9): ", pPlayer->name);
        scanf("%i", &chosenSpot); 
        getchar();
    }while ((chosenSpot < 1 && chosenSpot > 9) || (pPlayer->flag | pOpponent->flag) & (1 << (chosenSpot - 1)));
    pPlayer->flag |= (1 << (chosenSpot - 1));
    boardPrinter(pPlayer, pOpponent);
    checkConditionState(pPlayer->flag, (pPlayer->flag | pOpponent->flag), pGameConcluded);
    endOfTurn(pPlayer->name, *pGameConcluded);
}
void play(Player *pFirst, Player *pSecond){
    u_int32_t gameConcluded = 0x0;
    do{
        playerTurn(pFirst, pSecond, &gameConcluded);
        if (!gameConcluded){ playerTurn(pSecond, pFirst, &gameConcluded); }
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
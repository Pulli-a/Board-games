//comando per compilare dal terminale:
//gcc main.c card_game_core.c trash_functions.c titles.c -o CardGames
#include <stdio.h>
#include <unistd.h> //for sleep function

#include "headers/card_game_core.h"
#include "headers/trash_functions.h"
#include "headers/titles.h"

//ALL GLOBAL VARIABLES
int DECK_POINTER = 0;
Card* deck[52] = {0};
const char suit[ 4 ] = {'H', 'D', 'C', 'S'};
const char face[ 13 ] = 
                       {'A', '2', '3', '4', 
                        '5', '6', '7', '8',
                        '9', 'T', 'J', 'Q', 'K'};
//funcions of main
int print_intro();

//main function
int main(){
    int game = 0;
    while(1){
        game = print_intro();
        switch (game)
        {
        case 1:
            trash();
            break;

        case 0:
            return 0;

        default:
            printf("select a valid choiche\n");
            sleep(1);
            break;
        }
    }
    return 0;
}

//print intro stampa tutti i titoli e restituisce il gioco selezionato
int print_intro(){
    int game = 0;
    printf("welcome to:\n\n");
    print_main_title();
    printf("\n\n game made by- pulli\n");
    printf("press 'enter' to start\n");
    getchar();
    do{
        clear_terminal();
        //TODO: aggiungi il titolino "card games"
        printf("select the game:\n");
        printf("1) trash\n");
        printf("0) exit\n");
        scanf("%d", &game);
    }while(game < 0 && game > 1);
    return game;
}
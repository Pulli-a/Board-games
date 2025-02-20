#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "headers/globals.h"
#include "headers/card_game_core.h"


int shuffle(Card* deck[]){
    if(deck[0] != 0){
        for(int x = 0; x < 52; x++){
            free(deck[x]);
            deck[x] = 0;
        }
    }
    int t = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            Card *newcard = malloc(sizeof(Card));
            newcard->suite = i;
            newcard->face = j;
            newcard->shown = 0;
            do{
                t = rand() % 52;
            }while(deck[t] != 0);
            deck[t] = newcard;
        }
    }
    return 0;
}

//hand is an array of cards
//number_of_cards is the number of cards in the hand

int deal(Card*deck[], Card*hand[], int numer_of_cards){
    Card* temp = 0;
    int prev_deck_pointer;
    if(DECK_POINTER == 50){
        shuffle(deck);
        DECK_POINTER = 0;
    }
    int j = 0;
    prev_deck_pointer = DECK_POINTER;
    for(int i = prev_deck_pointer; i < (prev_deck_pointer+numer_of_cards); i++){
        hand[j] = deck[i];
        j++;
        DECK_POINTER++;
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//local libraries
#include "headers/globals.h"
#include "headers/card_game_core.h"
#include "headers/trash_functions.h"
#include "headers/titles.h"

#define AUDIO if(audio == 1)

int settings(int* game_speed, int* audio, int* pretty){
    char char_option = 'x';
    int int_option = 0;
    do{
        print_settings_logo();
        getchar();
        printf("select what you want to change:\n");
        printf("s) game speed\n");
        printf("a) audio\n");
        printf("g) grapic\n");
        //add more
        printf("e) exit settings menu\n");
        scanf("%c", &char_option);
        switch (char_option)
        {
        case 's':
            const char* speeds[] = {"fast", "medium", "slow"};
            print_settings_logo();
            do{
                printf("select the speed of the game\n");
                printf("current speed of the game: %s\n", speeds[*game_speed-1]);
                printf("1) fast\n2) medium\n3) slow\n");
                scanf("%d", &int_option);
            }while(int_option < 1 || int_option > 3 );
            *game_speed = int_option;
            break;
        case 'a':
            const char* audio_mode[] = {"off", "on"};
            print_settings_logo();
            do{
                printf("WARNING: audio doesn't work on some machine\n");
                printf("current state of audio: %s.\n", audio_mode[*audio]);
                printf("0) audio off\n1) audio on\n");
                scanf("%d", &int_option);
            }while( int_option< 0 || int_option > 1);
            *audio = int_option;
            break;
        case 'g':
            const char* graphic_mode[] = {"basic", "pretty"};
            print_settings_logo();
            do{
                printf("select the graphic of the game:\n");
                printf("current graphic mode: %s.\n", graphic_mode[*pretty]);
                printf("0) basic\n1) pretty\n");
                scanf("%d", &int_option);
            }while( int_option< 0 || int_option > 1);
            *pretty = int_option;
            break;
        case 'e':
            break;
        default:
            printf("please select a valid choice\n");
            sleep(2);
            break;
        }
    }while(char_option != 'e');
    return 0;
}

int print_tilte(){
    char choice;
    printf("Welcome to\n\n");
    print_trahs_title();
    printf("\n\ngame made by Pulli for Juice <3\npress'enter' to start\n");
    getchar();
    printf("Do you know how to play? (y/n)\n");
    scanf("%c", &choice);
    switch (choice)
    {
    case 'n':
    case 'N':
        printf("Trash is a game played by two people (in our case one is the computer).\n");
        printf("Each player starts with 10 cards flipped on the back\n");
        printf("every round a player draws a card and discards one.\n");
        printf("You can either draw form the deck or from the discard-pile called 'trash'.\n");
        printf("When you draw a card whose value corrisponds to a card not yet flipped\n");
        printf("you put the drawn card in that spot and take the one that was there\n");
        printf("you continue to do so untill you draw a card that you cannot place\n");
        printf("Kings and Queens instantly end your turn\n");
        printf("the Jack can be put in whatever available spot you have\n");
        printf("firs one to flip all cards wins\n");
        printf("you repeate the game but this time you have one card less\n");
        printf("first one to end the cards wins\n");
        printf("good luck\n(press enter to continue)\n\n");
        getchar();
        scanf("%c", &choice);
        break;
    
    default:
        printf("oks, Have fun then\n");
        sleep(1);
        break;
    }
    return 0;
}


void print_cards(Card* hand[],int cards, int pretty){
    if(pretty == 1){
        for(int i = 0; i < cards; i++){
            printf(".--. ");
        }
        printf("\n");
        for(int j = 0; j < cards; j++){
            if((hand[j]->shown) == 0){
                printf("|()| ");
            }else{
                printf("|%c%c| ", face[hand[j]->face], suit[hand[j]->suite]);
            }
        }
        printf("\n");
        for(int k = 0; k < cards; k++){
            printf("'--' ");
        }
    }
    else{
        for(int i = 0; i < cards; i++){
            if((hand[i]->shown) == 0){
                printf(" XX");
            }else{
                printf(" %c%c", face[hand[i]->face], suit[hand[i]->suite]);
            }
        }  
    }
    printf("\n");
}

void print_middle(Card* discard, int pretty){
    if(pretty == 1){
        if(discard == NULL){
            printf("\n\t  .--..\n");
            printf(  "\t  |()||\n");
            printf(  "\t  '--''\n");
        }
        else{
           printf("\n\t  .--..\t\t\t.--.\n");
           printf(  "\t  |()||\t\t\t|%c%c|\n",face[discard->face], suit[discard->suite]);
           printf(  "\t  '--''\t\t\t'--'\n");
        }
    }
    else{
        if(discard == NULL){
        printf("\n\tXX\t00\n");
        }else{
        printf("\n\tXX\t%c%c\n", face[discard->face], suit[discard->suite]);
        }
    }
    printf("\n");
}

int print_board(Card* hand_cpu[],Card* hand_plr[],int player_cards,int cpu_cards, Card* discard, int pretty){
    print_mini_game_logo();
    print_cards(hand_cpu, cpu_cards, pretty);
    print_middle(discard, pretty);
    print_cards(hand_plr, player_cards, pretty);
    printf("\n\n");
    return 0;
}

int did_i_win(Card* hand[], int cards, int cpu){
    for(int i = 0; i < cards; i++){
        if(hand[i]->shown == 0){
            return 0;
        }
    }
    if(cpu)
        return -1;
    return 1;
}

int print_hand(Card* hand[], int cards, Card* drawn, Card* discard, int cpu, int pretty){
    print_mini_game_logo();
    if(cpu == 0){
        printf("_.-'-._.-'|YOUR TURN|'-._.-'-._\n\n");
    }
    else{
        printf("_.-'-._.-'|CPU's TURN|'-._.-'-._\n\n");
    }
    print_cards(hand, cards, pretty);
    if(drawn != NULL && pretty == 1){
        printf("\n CARD DRAWN:\n");
        printf("   .--.\n");
        printf("   |%c%c|\n",face[drawn->face], suit[drawn->suite]);
        printf("   '--'\n");
    }else if(drawn != NULL)
        printf("\n\ncard drawn: %c%c\n\n", face[drawn->face], suit[drawn->suite]);
    return 0;
}

int play_the_game(Card* hand[], int cards, Card* drawn, Card** discard, int cpu, int speed, int pretty){
    //check if someone won
    int w = did_i_win(hand, cards, cpu);
    if(w) {
        return w;
    }
    //start play cycle
    print_hand(hand, cards, drawn, *discard, cpu, pretty);
    Card* temp = NULL;
    //drew king or queen
    if(drawn->face == 11 ||drawn->face == 12|| drawn->face == 13){
        *discard = drawn;
        sleep(speed);
    }
    //drew jack
    else if(drawn->face == 10){
        int position = 0; 
        //if the player is playing
        if(cpu == 0){
            print_hand(hand, cards, drawn, *discard, 0, pretty);
            do{
                printf("choose where to put it\n");
                scanf("%d", &position);
                position--;
            } while(position >= 0 && position < cards && hand[position]->shown != 0);
        }
        //if the cpu is playing
        else{
            do{
                position = rand()%cards;
            }while(hand[position]->shown != 0);
        }
        temp = hand[position];
        hand[position] = drawn;
        hand[position]->shown = 1;
        drawn = temp;
        sleep(speed);
        w = play_the_game(hand, cards, drawn, discard, cpu, speed, pretty);
    }
    //if you draw a card higher than the cards in your hand
    else if(drawn->face > cards-1){
        *discard = drawn;
        sleep(speed);
    }
    //if you can play the card
    else if(hand[drawn->face]->shown == 0){
        temp = hand[drawn->face];
        hand[drawn->face] = drawn;
        if(cpu == 0){
            print_hand(hand, cards, drawn, *discard, 0, pretty);
        }
        hand[drawn->face]->shown = 1;
        drawn = temp;
        sleep(speed);
        w = play_the_game(hand, cards, drawn, discard, cpu, speed, pretty);
    }
    //if the card is a jack
    else if(hand[drawn->face]->face == 10){
        temp = hand[drawn->face];
        drawn->shown = 1;
        hand[drawn->face] = drawn;
        drawn = temp;
        sleep(speed);
        w = play_the_game(hand, cards, drawn, discard, cpu, speed, pretty);
    }
    else{
        *discard = drawn;
        sleep(speed);
    }
    return w;
}


int trash(){
    //set-up the program variables
    srand(time(NULL));
    int playing = 1;
    int round = rand()%2; // decides who start
    Card* discard = NULL;
    Card* drawn = NULL;
    static int player_cards = 10;
    static int cpu_cards = 10;
    Card* hand_plr[10] = {0};
    Card* hand_cpu[10] = {0};
    int win_round;
    //settings for the game
    int game_speed = 2;
    int audio = 1;
    int pretty = 1;
    //start of the game
    print_tilte();
    while(player_cards != 0 || cpu_cards != 0){
        shuffle(deck);
        printf("shuffling the deck...\n");
        DECK_POINTER = 0;
        drawn = NULL;
        discard = NULL;
        sleep(2);
        if(round%2 == 0){
            deal(deck, hand_plr, player_cards);
            deal(deck, hand_cpu, cpu_cards);
        }
        else{
            deal(deck, hand_cpu, cpu_cards);
            deal(deck, hand_plr, player_cards); 
        }
        int turn = round%2 + 1;
        while(turn){
            win_round = 0;
            win_round = print_board(hand_cpu, hand_plr, player_cards, cpu_cards, discard, pretty);
            drawn = NULL;
            int move;
            if(turn % 2 != 0 && win_round == 0){
                AUDIO printf("\a\a");
                do{
                    printf("CHOOSE WHAT TO DO:\n");
                    printf("0- draw from deck\n");
                    if(turn != round%2 + 1)
                        printf("1- draw form trash\n");
                    printf("6- settings\n\n");
                    printf("-1 exit game\n");
                    scanf("%d", &move);
                    switch (move)
                    {
                    case 0:
                        drawn = deck[DECK_POINTER];
                        DECK_POINTER++;
                        turn++;
                        break;
                    case 1:
                        drawn = discard;
                        discard = NULL;
                        turn++;
                        break;
                    case 6:
                        settings(&game_speed, &audio, &pretty);
                        print_board(hand_cpu, hand_plr, player_cards, cpu_cards, discard, pretty);
                        break;
                    case -1:
                        return 0;
                    default:
                        printf("insert a valid choiche\n");
                        sleep(1);
                        break;
                    }
                }while(move < 0 || move > 1);
                play_the_game(hand_plr, player_cards, drawn, &discard, 0, game_speed, pretty);
            }
            else if(win_round == 0){
                sleep(2);
                if(discard != NULL && discard->face != 11 && discard->face != 12){
                    if((hand_cpu[discard->face]->shown == FALSE && discard->face <= cpu_cards - 1) || hand_cpu[discard->face]->face == JACK){
                        drawn = discard;
                        discard = NULL;
                    }
                    else{
                    drawn = deck[DECK_POINTER++];
                    }   
                }
                else{
                    drawn = deck[DECK_POINTER++];
                }
                play_the_game(hand_cpu, cpu_cards, drawn, &discard, 1, game_speed, pretty);
                turn ++;
            }
            if(cpu_cards == 0){
                printf("CPU WON :(\n");
                AUDIO printf("\a\a");
                return 0;
            }else if(player_cards == 0){
               printf("YOU WON :)\n");
               AUDIO printf("\a\a\a");
               return 0;
            }
            if(did_i_win(hand_plr, player_cards, 0) == 1){
                print_board(hand_cpu, hand_plr, player_cards, cpu_cards, discard, pretty);
                printf("YOU HAVE WON THIS ROUND!!\n");
                sleep(2);
                player_cards--;
                break;
            }
            else if(did_i_win(hand_cpu, cpu_cards, 1) == -1){
                print_board(hand_cpu, hand_plr, player_cards, cpu_cards, discard, pretty);
                printf("you have lost this round\n");
                sleep(2);
                cpu_cards--;
                break;
            }
        }
        round++;
    }
    return 0;
}


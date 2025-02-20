#ifndef _TRASH_FUNCTIONS_
#define _TRASH_FUNCTIONS_

int print_tilte();
int print_board(Card* hand_cpu[],Card* hand_plr[],int player_cards,int cpu_cards, Card* discard, int pretty);
int did_i_win(Card* hand[], int cards, int cpu);
int play_the_game(Card* hand[], int cards, Card* drawn, Card** discard, int cpu, int speed, int pretty);
int print_hand(Card* hand[], int cards, Card* drawn, Card* discard, int cpu, int pretty);
int settings(int* game_speed, int* audio, int* pretty);
int trash();

#endif
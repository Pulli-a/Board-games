#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "headers/pretty_print.h"
#include "headers/titles.h"
#include "headers/globals.h"

int open_file(FILE** filenamePtr, char* filename, char* mode);
int find_word(FILE* filenamePtr, int position, char word[]);

int guess_a_word(FILE* possible_words, Board* b, int* init);
int is_word_valid(char guess_word[], FILE* possible_word);
int eval_word(Board*b, char guess_word[]);
int print_wordle_board(Board* b, int* init);
void print_keyboard_map(Board b, int* init);


int wordle(){
    srand(time(NULL));
    FILE* allowed_words = NULL;
    FILE* possible_words = NULL;
    int err = 0;
    int init = 1;
    Board b = {
        .attempt = 0,
        .board = {0},
        .scores = {0},
        .word = {0}
    };
    err = open_file(&allowed_words, "data/allowed_words.txt", "r");
    err = open_file(&possible_words, "data/possible_words.txt", "r");
    if(err == 1) return 1;
    int word_position = rand()%2310;
    find_word(possible_words, word_position, b.word);
    fclose(possible_words);
    for(int i = 0; i < 6; i++){
        if(guess_a_word(allowed_words, &b, &init) == 1){
            print_wordle_board(&b, &init);
            print_word_color("\nYOU HAVE WON!!\n", PRINT_GREEN);
            sleep(2);
            break;
        }
        if(i == 5){
            print_wordle_board(&b, &init);
            print_word_color("\nyou have lost\n", PRINT_RED);
            printf("the word was: ");
            print_word_background_color(b.word, PRINT_BLUE);
            sleep(3);
        }
    }
    
    fclose(allowed_words);
    return 0;
}

int find_word(FILE* filenamePtr, int position, char word[]){
    if(filenamePtr != NULL){
        if(fseek(filenamePtr, position, SEEK_SET) == 0 ){
            do{
                fscanf(filenamePtr, "%s", word);
            }while(strlen(word)!= 5);
        }
    }
    return 1;
}

int open_file(FILE** filenamePtr, char* filename, char* mode){
    if(((*filenamePtr) = fopen(filename, mode)) == NULL){
        printf("error: can't open file %s", filename);
        return 1;
    }
    return 0;
}



int guess_a_word(FILE* allowed_words, Board* b, int* init){
    char guess_word[10] = {0};
    int did_i_win = 0;
    while(1){
        while(1){
            print_wordle_board(b, init);
            scanf("%s", guess_word);
            if(strlen(guess_word) == 5) break;
            else{
                print_word_color("word must be 5 letter long\n", PRINT_RED);
                sleep(1);
            }
        }
        if (is_word_valid(guess_word, allowed_words) == 0){
            did_i_win = eval_word(b, guess_word);
            b->attempt++;
            return did_i_win;
        }
        else{
            print_word_color("insert a valid word\n", PRINT_RED);
            sleep(1);
        }
    }
}
// TODO: stampa anche tutta la tastiera con mano a mano le lettere che cambiano colore per tenere
//       facilmente traccia dei tentativi fatti
int print_wordle_board(Board* b, int*init){
    clear_terminal();
    printf("wordle:\n");
    printf("=====================\n");
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
            printf("|");
            if(b->board[i][j] != 0){
                print_char_background_color(' ', b->scores[i][j]);
                print_char_background_color(b->board[i][j], b->scores[i][j]);
                print_char_background_color(' ', b->scores[i][j]);
            }
            else{
                printf("   ");
            }
        }
        printf("|\n");
        printf("=====================\n");
    }
    print_keyboard_map(*b, init);
}

int is_word_valid(char guess_word[], FILE* allowed_words){
    if(allowed_words != NULL){
        char attempt[10];
        rewind(allowed_words);
        while(!feof(allowed_words)){
            fscanf(allowed_words, "%s", attempt);
            if(strcmp(attempt, guess_word) == 0)
                return 0;
        }
        return 1;
    }
    return -1;
}

//TODO: non solo deve vedere se c'è ma quante volte e se quelle volte è già stato usato
// a volte confonde il fatto che una lettera già indovinata ricompaia gialla
int eval_word(Board* b, char guess_word[]){
    char c;
    int won = 1; 
    for(int i = 0; i < 5; i++){
        b->board[b->attempt][i] = guess_word[i];
    }
    //printf("%s",b->board[b->attempt]);
    for(int i = 0; i < 5; i++){
        if(guess_word[i] == b->word[i]){
            b->scores[b->attempt][i] = PRINT_GREEN;
        }
        else if(strchr(b->word, guess_word[i]) != NULL){
            b->scores[b->attempt][i] = PRINT_YELLOW;
            won = 0;
        }
        else{
            won = 0;
        }
    }
    return won;
}

void print_keyboard_map(Board b, int* init){
    static const char all_keyes[] = "qwertyuiop asdfghjkl zxcvbnm";
    static int all_scores[29];
    int spacing_count = 0;
    //set all elements of all_scores to PRINT_GRAY only at the start of the program
    if(*init == 1){
        *init = 0;
        for(int i = 0; i < 29; i++){
            all_scores[i] = PRINT_GRAY;
        }
    }
    //aggiorna i colori delle lettere della tastiera
    for(int k = 0; k < 5; k++){
        for(int i = 0; i < strlen(all_keyes); i++){
            if(b.board[b.attempt-1][k] == all_keyes[i]){
                all_scores[i] = b.scores[b.attempt-1][k];
                break;
            }
        }
    }
    //stampa la tastiera
    print_char_background_color(' ', PRINT_GRAY);
    for(int i = 0; i < strlen(all_keyes); i++){
        if(all_keyes[i] == ' '){
            printf("\n");
            for(int i = 0; i <= spacing_count;i++){
                printf(" ");
            }
            print_char_background_color(' ', PRINT_GRAY);
            spacing_count+= 2;
            continue;
        } 
        print_char_background_color(all_keyes[i], all_scores[i]);
        print_char_background_color(' ', PRINT_GRAY);
    }
    printf("\n\n");
}
#include <stdio.h>
#include "globals.h"

#ifndef _WORDLE_
#define _WORDLE_

    int wordle();
    int open_file(FILE** filenamePtr, char* filename, char* mode);
    int find_word(FILE* filenamePtr, int position, char word[]);

    int guess_a_word(FILE* possible_words, Board* b, int* init);
    int is_word_valid(char guess_word[], FILE* possible_word);
    int eval_word(Board*b, char guess_word[]);
    int print_wordle_board(Board* b, int* init);
    void print_keyboard_map(Board b, int* init);

#endif
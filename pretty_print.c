#include <stdio.h>

#include "headers/pretty_print.h"

int print_word_color(char text[], int color){
    if((color > 30 && color <38) || color == 0){
        printf("\033[%dm%s", color, text);
        //riporta il terminale bianco
        printf("\033[%dm", PRINT_WHITE);
        return 0;
    }
    return 1;
}

int print_char_color(char letter, int color){
    if((color > 30 && color <38) || color == 0){
        printf("\033[%dm%c", color, letter);
        //riporta il terminale bianco
        printf("\033[%dm", PRINT_WHITE);
        return 0;
    }
    return 1;
}

int print_word_background_color(char text[], int color){
    if((color > 30 && color <38) || color == 0){
        printf("\033[%dm%s", color+10, text);
        //riporta il terminale bianco
        printf("\033[%dm", 40); //40 -> black background
        return 0;
    }
    return 1;
}

int print_char_background_color(char letter, int color){
    if((color > 30 && color <38) || color == 0){
        printf("\033[%dm%c", color+10, letter);
        //riporta il terminale bianco
        printf("\033[%dm", 40); //40 -> black background
        return 0;
    }
    return 1;
}
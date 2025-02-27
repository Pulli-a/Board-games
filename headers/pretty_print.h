
#ifndef _PRETTY_PRINT_
#define _PRETTY_PRINT_

    //to add colors goto https://man7.org/linux/man-pages/man5/terminal-colors.d.5.html
    //volendo si può cambiare il back ground ma non mi serve quindi non lo faccio
    #define PRINT_RED 31
    #define PRINT_GREEN 32
    #define PRINT_YELLOW 33
    #define PRINT_BLUE 34
    #define PRINT_PURPLE 35
    #define PRINT_CYAN 36
    #define PRINT_GRAY 37
    #define PRINT_WHITE 0

    int print_word_color(char text[], int color);
    int print_char_color(char letter, int color);
    int print_word_background_color(char text[], int color);
    int print_char_background_color(char letter, int color);



#endif
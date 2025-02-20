//basic boolean definitio
#define FALSE 0
#define TRUE 1
//definition of "special cards"
#define ACE 0
#define JACK 10
#define QUEEN 11
#define KING 12
//definition of cards

extern const char face[13];
extern const char suit[4];

//important variable for program
typedef struct card{
    int suite;
    int face;
    int shown;
}Card;
extern int DECK_POINTER;
extern Card* deck[52];
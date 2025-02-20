/** \file card_game_core.h
 * \brief has all core funcion for a card game
 * \author Alessandro Maryni
 */

#include "globals.h"

#ifndef _CARD_GAME_CORE_
#define _CARD_GAME_CORE_

int shuffle(Card* deck[]);
int deal(Card*deck[], Card*hand[], int numer_of_cards);

#endif
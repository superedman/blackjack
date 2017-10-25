#include "card.h"
#include <vector>

#ifndef BLACKJACK_BLACKJACK_H
#define BLACKJACK_BLACKJACK_H

//prototypes...
void determineWinner(int, int);
int getRandomNumber(int, int);
void printDeck(vector<card> &);
void playBlackJack(void);
vector<card> buildDeck(void);
string convertIntToSuit(int);
card dealNextCard (vector<card> &);
void shuffleDeck(vector<card> &);
card hit(vector<card> &, int &, int, vector<card> &, bool);
void dealCards(vector<card> &, int &, int, vector<card> &);
int computeScore(vector<card> &);

#endif //BLACKJACK_BLACKJACK_H

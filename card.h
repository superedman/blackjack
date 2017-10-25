#include <iostream>
#include <string>

using namespace std;


#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

struct card {
    int rank;
    string suit;
    void printCard(void) {
        string rankString;
        if (rank == 1) {
            rankString = "Ace";
        } else if (rank > 1 && rank < 11) {
            rankString = std::to_string(rank);
        } else if (rank == 11) {
            rankString = "Jack";
        } else if (rank == 12) {
            rankString = "Queen";
        } else {
            rankString = "King";
        }
        cout << rankString << " of " << suit << endl;
    };
};

#endif //BLACKJACK_CARD_H

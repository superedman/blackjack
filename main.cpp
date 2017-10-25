//Specification: This program plays a version of
//the card game of 21.
//A human player is pitted against the computer.
//The player who is the closest to 21 without
//going over wins the hand.

#include "blackjack.h"

int main() {
    string keepPlaying = "No"; //loop control variable

    do {
        playBlackJack();

        //ask if want to keep playing?
        cout << "Do you want to play another hand (Yes/No)?";
        cin >> keepPlaying;
        cout << endl;
    } while(keepPlaying == "Yes" || keepPlaying == "yes");
}
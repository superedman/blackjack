//Specification: This program plays a version of
//the card game of 21.
//A human player is pitted against the computer.
//The player who is the closest to 21 without
//going over wins the hand.

#include <algorithm>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "card.h"

using namespace std;

//prototypes...
void play21(void);

void determineWinner(int, int);
int getRandomNumber(int, int);
void printDeck(vector<card> &);
void playBlackJack(void);
vector<card> buildDeck(void);
string convertIntToSuit(int);
card dealNextCard (vector<card> &);
void shuffleDeck(vector<card> &);
void hit(vector<card> &, int &, int);
void dealCards(vector<card> &, int &, int);

int main() {
    string keepPlaying = "No"; //loop control variable

    do {
        playBlackJack();

        //ask if want to keep playing?
        cout << "Do you want to play another hand (Yes/No)?";
        cin >> keepPlaying;
    } while(keepPlaying == "Yes" || keepPlaying == "yes");
}

void playBlackJack(void) {
    vector<card> theDeck = buildDeck();
    int playerScore = 0;
    int dealerScore = 0;

    // Deal player cards
    dealCards(theDeck, playerScore, 0);

    // Deal dealer cards
    dealCards(theDeck, dealerScore, 1);

    string hitOrStand = "";
    // Player hit or stand?
    do {
        // While hit && playerScore <= 21, continue
        // If playerScore > 21, bust, game over
        cout << "Your score is " << playerScore << endl;
        cout << "Hit or Stand?";
        cin >> hitOrStand;
        cout << endl;

        if (hitOrStand == "Hit") {
            hit(theDeck, playerScore, 0);
            cout << "You chose to hit. You now have " << playerScore << endl;
        }
    } while ((hitOrStand == "Hit" || hitOrStand == "hit") && playerScore <= 21);

    if (playerScore > 21) {
        determineWinner(playerScore, dealerScore);
        // Player busted. We're done.
        return;
    }

    // Time for the dealer
    // While dealerScore < 17, hit
    // If dealerScore > 21, bust, game over
    cout << "Dealer score is " << dealerScore << endl;
    while (dealerScore < 17) {
        hit(theDeck, dealerScore, 1);
    }

    // Determine winner
    determineWinner(playerScore, dealerScore);

//    while (theDeck.size() > 0) {
//        card next = dealNextCard(theDeck);
//        cout << "Next card up is: ";
//        next.printCard();
//        cout << "Size of the deck is now " << theDeck.size();
//        cout << endl;
//        cout << endl;
//    }
}

void dealCards(vector<card> &deck, int &score, int playerOrDealer) {
    card one = dealNextCard(deck);
    card two = dealNextCard(deck);

    score = score + one.rank;
    score = score + two.rank;

    if (playerOrDealer == 0) {
        cout << "You were dealt the " << one.rank << " of " << one.suit << endl;
        cout << "You were dealt the " << two.rank << " of " << two.suit << endl;
        cout << "Your total is: " << score << endl << endl;
    } else {
        cout << "Dealer shows the " << two.rank << " of " << two.suit << endl;
        cout << "Dealer total is " << two.rank << endl << endl;
    }
}

void hit(vector<card> &deck, int &score, int playerOrDealer) {
    card newCard = dealNextCard(deck);

    score = score + newCard.rank;

    if (playerOrDealer == 0) {
        cout << "You were dealt the " << newCard.rank << " of " << newCard.suit << endl;
        cout << "Your total is: " << score << endl << endl;
    } else {
        cout << "Dealer was dealt the " << newCard.rank << " of " << newCard.suit << endl;
        cout << "Dealer total is " << score << endl << endl;
    }
}

card dealNextCard (vector<card> & deck) {
    card next;
    next.suit = deck.back().suit;
    next.rank = deck.back().rank;
    deck.pop_back();
    return next;
}

vector<card> buildDeck() {
    // Create Vector
    vector<card> deck;
    // Add 52 cards
    for (int x=0; x<4; ++x) {
        for (int y=1; y<14; ++y) {
            card newCard;
            newCard.suit = convertIntToSuit(x);
            if (y > 10) {
                newCard.rank = 10;
            } else {
                newCard.rank = y;
            }
            deck.push_back(newCard);
        }
    }

    // Print out the deck for debugging
//    printDeck(deck);
    // Shuffle the deck
    shuffleDeck(deck);
    // Print Deck again
//    cout << endl;
//    printDeck(deck);

    return deck;
}

/*
* Converts a number between 0 and 3 to a corresponding
* playing card suit
*/
string convertIntToSuit(int suitNum) {
    switch( suitNum ) {
        case 0:
            return "Hearts";
        case 1:
            return "Clubs";
        case 2:
            return "Diamonds";
        case 3:
        default:
            return "Spades";
    }
}

void printDeck(vector<card> & deck) {
    for(std::vector<card>::iterator it = deck.begin(); it != deck.end(); ++it) {
        (*it).printCard();
    }
}

void shuffleDeck(vector<card> & deck) {
    // Init random
    srand(time(NULL));
    // Number of times to switch 2 random cards in the deck
    int numTimes = 3000;
    for (int x=0; x<numTimes; ++x) {
        int firstSpot = getRandomNumber(0, 51);
        int secondSpot = getRandomNumber(0, 51);
        swap(deck[firstSpot], deck[secondSpot]);
    }
}

void determineWinner(int playerScore, int dealerScore) {
//Compare the scores to see who won
//Both the human and the dealer score totals are provided as arguments
//Display total scores and indicate winner
//possible outcomes: human wins, computer wins, tie
    if (playerScore > 21) {
        cout << "Your score is " << playerScore << " - you busted! Thanks for playing!" << endl;
    } else if (dealerScore > 21) {
        cout << "Dealer score is " << dealerScore << " - the dealer busted! You win!";
    } else if (playerScore > dealerScore) {
        cout << "Player score is " << playerScore << endl;
        cout << "Dealer score is " << dealerScore << endl;
        cout << "You win!" << endl;
    } else if (dealerScore > playerScore) {
        cout << "Player score is " << playerScore << endl;
        cout << "Dealer score is " << dealerScore << endl;
        cout << "You lose. Thanks for playing!" << endl;
    } else {
        cout << "Player score is " << playerScore << endl;
        cout << "Dealer score is " << dealerScore << endl;
        cout << "It's a draw! Thanks for playing!" << endl;
    }
}

int getRandomNumber(int lowerLimit, int upperLimit) {
    //returns a random number within the given boundary
    return rand() % (upperLimit - lowerLimit + 1);
}
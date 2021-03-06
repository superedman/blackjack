//Specification: This program plays a version of
//the card game of 21.
//A human player is pitted against the computer.
//The player who is the closest to 21 without
//going over wins the hand.

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "card.h"

using namespace std;

//prototypes...
void play21(void);

int dealCards(int, string);
void hit(int &);
void determineWinner(int, int);
int Random(int, int);
void printCard(card);
void playBlackJack(void);
vector<card> buildDeck(void);
string determineSuit(int);
card dealNextCard (vector<card>);

int main() {
    char keepPlaying = 'n'; //loop control variable

    do {
        playBlackJack();

        //ask if want to keep playing?
        cout << "Do you want to play another hand (y/n)?";
        cin >> keepPlaying;
    } while(keepPlaying == 'Y' || keepPlaying == 'y');
}

void playBlackJack(void) {
    buildDeck();

}

card dealNextCard (vector<card> & deck) {

}

vector<card> buildDeck() {
    // Create Vector
    vector<card> deck;
    // Add 52 cards
    card aceOfSpades;
    aceOfSpades.rank = 11;
    aceOfSpades.suit = "Spade";
    deck.push_back(aceOfSpades);

    for (int x=0; x<4; ++x) {
        for (int y=1; y<14; ++y) {
            card newCard;
            newCard.suit = determineSuit(x);
            newCard.rank = y;
            deck.push_back(newCard);
        }
    }

    printCard(aceOfSpades);

    // Shuffle the deck

}

string determineSuit(int suitNum) {
    if (suitNum == 0) {
        return "Hearts";
    } else if (suitNum == 1) {
        return "Diamonds";
    } else if (suitNum ==2) {
        return "Spades";
    } else {
        return "Clubs";
    }
}

void printCard(card c) {
    cout << c.suit << " " << c.rank << endl;
}

void play21(void) {
    //play one hand of 21

    //randomize the cards
    srand((int) time(0));

    // deals the cards
    int person = dealCards(2, "Your Cards:");
    cout << " = " << person << endl;
    int house = dealCards(2, "Computers Cards:");
    cout << " = " << house << endl;

    // Ask if they want a hit and keep hitting...
    hit(person);
    cout << endl;

    //Determine if the computer takes a hit
    while ((house < person) && (house <= 21) && (person <= 21)) {
        house += dealCards(1, "The Computer takes a card ");
        cout << endl;
    }
    //show who won....
    determineWinner(person, house);
}

//This function deals the cards
//The number of cards to be dealt is provided as an argument
//A message indicating which player is receiving the cards is also
//given as an argument
//The player message and the cards dealt is displayed to the screen
// total value of the dealt cards is returned
int dealCards(int numberOfCards, string message) {
    int ret_val = 0, val;
    int cards = numberOfCards;

    cout << message;
    while(cards--) {
        // Values from 1 to K
        val = Random(0,14);
        if( val > 10 ) val = 10;
        if( val == 1 ) val = 11;
        cout << val;
        if(cards)
            cout << ",";
        ret_val+=val;
    }
    return ret_val;
}

void determineWinner(int humanScore, int houseScore) {
//Compare the scores to see who won
//Both the human and the house score totals are provided as arguments
//Display total scores and indicate winner
//possible outcomes: human wins, computer wins, tie
}

void hit(int &playerScore) {
//This function asks if they want another card -- 'a hit'
//the player's score total is accumulated as they take cards
//the player can continue taking cards until they wish to stop or they exceed 21
//After a card is taken (use the dealCards function) the user's current total is displayed
//If the user goes over 21 'busted' is displayed

}

int Random(int lowerLimit, int upperLimit) {
//returns a random number within the given boundary
    return 1 + rand() % (upperLimit - lowerLimit + 1);
}
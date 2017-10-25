#include <algorithm>
#include <iostream>
#include <vector>
#include "card.h"
#include "blackjack.h"

bool checkBlackJack(int score, int playerOrDealer) {
    if (score == 21) {
        if (playerOrDealer == 0) {
            cout << "You got BlackJack!" << endl;
        } else {
            cout << "Dealer got BlackJack. Sorry, you're a loser." << endl;
        }
        return true;
    }
    return false;
}

void playBlackJack(void) {
    vector<card> theDeck = buildDeck();
    int playerScore = 0;
    int dealerScore = 0;

    // Create card history
    vector<card> playerCardHistory;
    vector<card> dealerCardHistory;

    // Deal player cards
    dealCards(theDeck, playerScore, 0, playerCardHistory);

    // Check for BlackJack here
    bool blackjack = checkBlackJack(playerScore, 0);
    if (blackjack) {
        return;
    }

    // Deal dealer cards
    dealCards(theDeck, dealerScore, 1, dealerCardHistory);

    // Check for BlackJack here
    blackjack = checkBlackJack(dealerScore, 1);
    if (blackjack) {
        return;
    }

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
            hit(theDeck, playerScore, 0, playerCardHistory, false);
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
    while (dealerScore < 17) {
        hit(theDeck, dealerScore, 1, dealerCardHistory, false);
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

void dealCards(vector<card> &deck, int &score, int playerOrDealer, vector<card> &cardHistory) {
    card one = hit(deck, score, playerOrDealer, cardHistory, true);
    card two = hit(deck, score, playerOrDealer, cardHistory, true);

    string rank = "";

    if (playerOrDealer == 0) {
        rank = to_string(one.rank);
        if (one.rank == 11) {
            rank = "Ace";
        }
        cout << "You were dealt the " << rank << " of " << one.suit << endl;

        rank = to_string(two.rank);
        if (two.rank == 11) {
            rank = "Ace";
        }
        cout << "You were dealt the " << rank << " of " << two.suit << endl;
        cout << "Your total is: " << score << endl << endl;
    } else {
        rank = to_string(two.rank);
        if (two.rank == 11) {
            rank = "Ace";
        }

        cout << "Dealer shows the " << rank << " of " << two.suit << endl;
        cout << "Dealer total is " << two.rank << endl << endl;
    }
}

card hit(vector<card> &deck, int &score, int playerOrDealer, vector<card> &cardHistory, bool silent) {
    card newCard = dealNextCard(deck);
    cardHistory.push_back(newCard);

    int newScore = computeScore(cardHistory);

    score = newScore;

    string rank = "";
    rank = to_string(newCard.rank);
    if (newCard.rank == 11) {
        rank = "Ace";
    }

    if (!silent) {
        if (playerOrDealer == 0) {
            cout << "You were dealt the " << rank << " of " << newCard.suit << endl;
            cout << "Your total is: " << score << endl << endl;
        } else {
            cout << "Dealer was dealt the " << newCard.rank << " of " << newCard.suit << endl;
            cout << "Dealer total is " << score << endl << endl;
        }
    }

    return newCard;
}

int computeScore(vector<card> &cardHistory) {
    int theScore = 0;
    for (int i=0; i<cardHistory.size(); ++i) {
        int currentCardRank = cardHistory.at(i).rank;
        if (currentCardRank == 11) {
            if (theScore + currentCardRank > 21) {
                currentCardRank = 1;
            }
        }
        theScore = theScore + currentCardRank;
    }
    return theScore;
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
            } else if (y == 1) {
                newCard.rank = 11;
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
        cout << "Dealer score is " << dealerScore << " - the dealer busted! You win!" << endl;
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

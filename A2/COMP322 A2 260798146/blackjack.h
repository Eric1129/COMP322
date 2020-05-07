/**
 * COMP322 2020Winter A2
 * Eric Shen, McGill ID 260798146
 */

#ifndef COMP322A2_BLACKJACK_H
#define COMP322A2_BLACKJACK_H

#include <vector>
// This is my header file
// which declares all classes and methods

using namespace std;

enum Rank{
    ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Type{
    CLUBS=1, DIAMONDS, HEARTS, SPADES
};

class Card : public error_condition {
private:
    Rank aRank;
    Type aType;

public:
    Card(Rank pRank,Type pType);
    int getValue() const;
    void displayCard();
};

class Hand{
public:
    vector<Card> aHand;
    void add(Card pCard);
    void clear();
    int getTotal() const;

};

class Deck{
private:
    vector<Card> aDeck;
public:
    void Populate();
    void shuffle();
    Card deal();
};

class AbstractPlayer: public Hand{

public:
    virtual bool isDrawing() const = 0;
    bool isBusted();
};


class ComputerPlayer: public AbstractPlayer{

public:
    bool isDrawing() const;
};

class HumanPlayer: public AbstractPlayer{

public:
    bool isDrawing() const;
    void announce(int i);
};

class BlackJackGame {
private:
    Deck m_deck;
    ComputerPlayer m_casino;
    HumanPlayer m_player;

public:
    int play();
};

#endif //COMP322A2_BLACKJACK_H

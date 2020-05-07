/**
 * COMP322 2020Winter A2
 * Eric Shen, McGill ID 260798146
 */

#include <iostream>
#include "blackjack.h"
#include <algorithm>
#include <random>

using namespace std;

//all my implementation of methods

Card::Card(Rank pRank,Type pType) {
    aRank = pRank;
    aType = pType;
}

// For rank J Q K they are 10
// others are their own rank (ACE is 1), I'll handle it later
int Card::getValue() const{
    if(aRank == JACK || aRank == QUEEN || aRank == KING){
        return 10;
    } else{
        return aRank;
    }
}

// Same, for rank J Q K , display them differently
// and other ranks are displayed as itself
void Card::displayCard(){
    if(aRank == JACK || aRank == QUEEN || aRank == KING){
        if(aRank == JACK){
            cout << "J";
        }
        else if(aRank == QUEEN){
            cout << "Q";
        }
        else {
            cout<< "K";
        }
    }
    else{
        cout << aRank ;
    }
    if(aType == CLUBS){
        cout << "C " ;
    }
    if(aType == DIAMONDS){
        cout << "D " ;
    }
    if(aType == HEARTS){
        cout << "H " ;
    }
    if(aType == SPADES){
        cout << "S " ;
    }
}

// I use vector method to add one at end
void Hand::add(Card pCard){
    aHand.push_back(pCard);
}

// I use vector method to clear
void Hand::clear(){
    aHand.clear();
}

// I loop the whole hand to get total value
// During loop, I also check ACE
// If there is ACE, I don't add to total first, I track the number of ACE
// After I add all other cards, I add ACEs back as 11
// if total exceeds 21, I switch one ACE from 11 to 1
// Thus it makes sure we have largest value if not exceed
int Hand::getTotal() const{
    int total = 0;
    int aceNumber = 0;
    for(int i = 0; i < aHand.size(); i++){
        int val = aHand.at(i).getValue();
        if(val == 1){
            aceNumber++;
        } else{
            total += val;
        }
    }

    total += 11*aceNumber;
    for(int i = 0; i < aceNumber; i++){
        if( total > 21){
            total -= 10;
        }
    }

    return total;
}

// Before I create all cards, clean deck first
// I loop
void Deck::Populate(){
    aDeck.clear();
    for(Rank r = ACE; r != KING + 1; r = static_cast<Rank>(r + 1)){
        for(Type t = CLUBS; t != SPADES + 1; t = static_cast<Type>(t + 1)){
            aDeck.push_back(Card(r,t));
        }
    }
}

// I use random and algorithm library to do shuffle
void Deck::shuffle(){
    random_device rd;
    ::shuffle(begin(aDeck),end(aDeck),rd);
}

// Since I'll shuffle the card every time
// I'll
Card Deck::deal(){
    Card temp = aDeck.front();
    aDeck.erase(aDeck.begin());
    return temp;
}

// Since my Abstruct player is inherited from Hand
// I can call hand method to check if our value is greater than 21
bool AbstractPlayer::isBusted() {
    return getTotal() > 21;
}

// Computer will draw if total less than 16
bool ComputerPlayer::isDrawing() const {
    return getTotal()<16;
}

// I use some input/output to decide player's choice
bool HumanPlayer::isDrawing() const {
        char wantToDraw;
        cout << "Do you want to draw? (y/n): ";
        cin >> wantToDraw;
        cout << endl;
        if(wantToDraw == 'y'){
            return true;
        }
        return false;
}

// Since prof want us announce just print game result
// I use a flag int to switch different case
void HumanPlayer::announce(int i) {
    if(i == 0){
        cout << "Player wins. " << endl;
    } else if(i == 1){
        cout << "Casino wins. " << endl;
    } else{
        cout << "Push: No one wins. " << endl;
    }
}

// My play method
int BlackJackGame::play(){
    // Everytime before play
    // Have a brand new deck
    m_deck.Populate();

    // We get casino initial card, display it and print it
    m_deck.shuffle();
    Card a = m_deck.deal();
    cout << "Casino: " ;
    a.displayCard();
    m_casino.add(a);
    cout << "[" << m_casino.getTotal() << "]" << endl;

    // Then we get player initial cards, display them and print them
    cout << "Player: " ;
    m_deck.shuffle();
    Card b = m_deck.deal();
    b.displayCard();
    m_deck.shuffle();
    Card c = m_deck.deal();
    c.displayCard();
    m_player.add(b);
    m_player.add(c);
    cout << "[" << m_player.getTotal() << "]" << endl;

    // Then player starts his turn
    // Use a while loop to keep track of player want to keep drawing or not
    while(m_player.isDrawing()){
        // If player draws, add new card to his hand
        cout << "Player: " ;
        m_deck.shuffle();
        Card c = m_deck.deal();
        m_player.add(c);

        // Then display all his cards, and total value
        for(Card c : m_player.aHand){
            c.displayCard();
        }
        cout << "[" << m_player.getTotal() << "]" << endl;

        // After that check if player busts
        if(m_player.isBusted()){
            cout << "Player busts. " << endl;
            // Call my announce method to print result
            m_player.announce(1);

            //If current round over, clear two players hand
            m_player.clear();
            m_casino.clear();
            return 0;
        }
    }

    // After player finished, becomes to casino turn
    // Basically the same
    while(m_casino.isDrawing()){
        cout << "Casino: " ;
        m_deck.shuffle();
        Card c = m_deck.deal();
        m_casino.add(c);
        for(Card c : m_casino.aHand){
            c.displayCard();
        }
        cout << "[" << m_casino.getTotal() << "]" << endl;
        if(m_casino.isBusted()){
            cout << "Computer busts. " << endl;
            m_player.announce(0);

            //
            m_player.clear();
            m_casino.clear();
            return 0;
        }
    }

    // If no one busts
    if(m_player.getTotal()>m_casino.getTotal()){
        m_player.announce(0);
    } else if(m_player.getTotal() < m_casino.getTotal()){
        m_player.announce(1);
    } else{
        m_player.announce(2);
    }

    //Before round over, clear two players' hands
    m_player.clear();
    m_casino.clear();
    return 0;
}
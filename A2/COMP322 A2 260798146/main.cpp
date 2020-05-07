/**
 * COMP322 Winter2020 A2
 * Eric Shen, McGill ID 260798146
 */

#include <iostream>
#include "blackjack.h"

using namespace std;

// The main method from handout
int main(){
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;

    BlackJackGame game;
    bool playAgain = true;
    char anser = 'y';
    while(playAgain){
        game.play();
        //Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): ";
        cin >> anser;
        cout << endl << endl;
        playAgain = (anser == 'y');
    }
    cout << "Game over!";
    return 0;
}

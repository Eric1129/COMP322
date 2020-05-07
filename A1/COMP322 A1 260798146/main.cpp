/**
 *  Follwing code is for COMP322 A1
 *  Created by Eric Shen on 2020/1/29.
 *  McGill ID 260798146
 */
#include <iostream>
#include <limits>
#include "functions.h"

using namespace std;
// This is my main function
int main() {

    // Just call this function to print the intro
    greetAndInstruct();

    // I create a random char array contains 27 char and initialize it full of different chars which are not 'X' and 'O'
    char board[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','Z'};

    // I create string reply to store player's reply for start or quit (y/n)
    string reply;
    cin >> reply;
    while( reply != "y" && reply != "n"){
        // If player inputs something else, program will ask again
        cout << "Illegal Response! Try again!"<< endl;
        cin >> reply;
    }
    if( reply == "y"){
        // Once player starts the game, system prints a new board
        cout << "Game starts!"<< endl;
        displayBoard(board);
        // Game will always continue until there is a winner or a tie
        // I handle the tie situation in checkWinner function
        while (!checkWinner(board)){
            // Player moves first
            cout << "Notify your move: "<< endl;
            // I store player input in an int
            int x;
            cin >> x;
            // handle the situation that player input is not an integer
            // In this situation player will be always asked until player has a correct input
            while (cin.fail())
            {
                cout << "Move should be an integer! Try again!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> x;
            }
            // Once player inputs an integer
            // I call checkIfLegal to make sure this position is ok to put
            // But since the first
            if(checkIfLegal(x-1,board)){
                // The char of this position in the array is replaced by 'X'
                // then display
                board[x-1] = 'X';
                displayBoard(board);
                // I check the winner every time when player made his move
                if(checkWinner(board)){
                    // If player wins, program ends
                    // If there is a tie, program also ends
                    cout << "You win! "<< endl;
                    return 0;
                }
                // I check tie situation here after player moves
                // Since handout says player moves first, then tie situation can only be after player moves
                // Because there has odd number of positions
                // If all positions are occupied
                // counter should be 27
                // Then program exits
                int counter = 0;
                for(int i =0; i<27; i++){
                    if(board[i] == 'O' || board[i] == 'X'){
                        counter++;
                    }
                }
                if(counter == 27){
                    cout<< "Game over! It is a Tie!" << endl;
                    return 0;
                }
                // If game can still move
                // Computer moves after player, and I call computerMove to let computer move
                cout << "Computer move: "<< endl;
                computerMove(board);
                displayBoard(board);
                // Once computer moved and displayed
                // I check the winner again that if there is a winner, it should be computer
                // or if there is a tie
                if(checkWinner(board)){
                    cout << "Computer win! "<< endl;
                    return 0;
                }
                int counter2 = 0;
                for(int i =0; i<27; i++){
                    if(board[i] == 'O' || board[i] == 'X'){
                        counter2++;
                    }
                }
                if(counter2 == 27){
                    cout<< "Game over! It is a Tie!" << endl;
                    return 0;
                }
                // If game can still move
            } else{
                cout << "Wrong place!"<< endl;
            }
        }
    }
    else{
        // When player inputs n means the game should be quit
        cout << "Game quit!"<< endl;
        return 0;
    }
    return 0;
}

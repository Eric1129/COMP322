/**
 * Following code is for COMP322 A1
 * Created by Eric Shen on 2020/1/29.
 * McGill ID is 260798146
 */

#include <iostream>

using namespace std;

//Q1
// I just print out all intro
void greetAndInstruct(){
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\n"
                 "The board is numbered from 1 to 27 as per the following: \n"
                 "\n"
                 " 1|2|3   10|11|12   19|20|21\n"
                 " -----   --------   --------\n"
                 " 4|5|6   13|14|15   22|23|24\n"
                 " -----   --------   --------\n"
                 " 7|8|9   16|17|18   25|26|27\n"
                 "\n"
                 "Player starts first. Simply input the number of the cell you want to occupy.\n"
                 "Player’s move is marked with X. Computer’s move is marked with O.\n"
                 "Start? (y/n):" << endl;
}


//Q2
// I create another string array to keep numbers 1-27 to display
// I only replace the 'X' and 'O' in the char array to string
void displayBoard (char board[]){
    string myBoard[27] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27"};
    // I start from board[0] to transform char array to my string array
    for(int i=0; i<27;i++){
        if(board[i] == 'X' || board[i] == 'O'){
            myBoard[i] = board[i];
        }
    }
    // Then just print the board
    cout << " " << myBoard[0] << " | " << myBoard[1] << " | " << myBoard[2] << "     " << myBoard[9] << " | "
    << myBoard[10] << " | " << myBoard[11] << "         " << myBoard[18] << " | " << myBoard[19] << " | " << myBoard[20] << endl;
    cout <<   " ---------    -------------     --------------- " << endl;
    cout << " " << myBoard[3] << " | " << myBoard[4] << " | " << myBoard[5] << "     " << myBoard[12] << " | "
              << myBoard[13] << " | " << myBoard[14] << "         " << myBoard[21] << " | " << myBoard[22] << " | " << myBoard[23] << endl;
    cout <<   " ---------    -------------     --------------- " << endl;
    cout << " " << myBoard[6] << " | " << myBoard[7] << " | " << myBoard[8] << "     " << myBoard[15] << " | "
              << myBoard[16] << " | " << myBoard[17] << "         " << myBoard[24] << " | " << myBoard[25] << " | " << myBoard[26] << endl;
    cout << "\n" << endl;
}

//Q3
// Every int above 26 and below 0 is not a valid move, since array position from 0 to 26
bool checkIfLegal (int cellNbre, char board[]){
    if(cellNbre > 26 || cellNbre < 0){
        return false;
    }
    else {
        // and every move position is already occupied is also not a valid move
        if(board[cellNbre] == 'X' || board[cellNbre] == 'O'){
            return false;
        }
        else{
            return true;
        }
    }
}

// I check if there is a winner by following situations
bool checkWinner(char board[]){
    // 2D
    // horizontal
    for(int i = 0; i < 26; i = i + 3 ){
        if(board[i] == board[i + 1] && board[i+1] == board[i+2]){
            return true;
        }
    }
    // Vertical
    for(int i = 0; i <=2; i++){
        if(board[i] == board[i+3] && board[i+3] == board[i+6]){
            return true;
        }
    }
    for(int i = 9; i <= 11; i++){
        if(board[i] == board[i+3] && board[i+3] == board[i+6]){
            return true;
        }
    }
    for(int i = 18; i <= 20; i++){
        if(board[i] == board[i+3] && board[i+3] == board[i+6]){
            return true;
        }
    }
    // Diagonal
    for(int i = 0; i <= 26; i = i + 9){
        if(board[i] == board[i+4] && board[i+4] == board[i+8]){
            return true;
        }
    }
    for(int i = 2; i <= 26; i = i + 9){
        if(board[i] == board[i+2] && board[i+2] == board[i+4]){
            return true;
        }
    }
    // 3D
    // 3D horizontal
    for(int i = 0; i <= 6; i = i+3 ){
        if(board[i] == board[i+10] && board[i+10] == board[i+20]){
            return true;
        }
    }
    for(int i = 2; i <= 8; i = i+3 ){
        if(board[i] == board[i+8] && board[i+8] == board[i+16]){
            return true;
        }
    }
    // 3D Vertical
    for(int i = 0; i <= 2; i++ ){
        if(board[i] == board[i+12] && board[i+12] == board[i+24]){
            return true;
        }
    }
    for(int i = 6; i <= 8; i++ ){
        if(board[i] == board[i+6] && board[i+6] == board[i+12]){
            return true;
        }
    }
    // 3D same point
    for(int i = 0; i<= 8; i++){
        if(board[i] == board[i+9] && board[i+9] == board[i+18]) {
            return true;
        }
    }
    // 3D diagonal
    if(board[0] == board[13] && board[13] == board[26]){
        return true;
    }
    if(board[2] == board[13] && board[13] == board[24]){
        return true;
    }
    if(board[6] == board[13] && board[13] == board[20]){
        return true;
    }
    if(board[8] == board[13] && board[13] == board[18]){
        return true;
    }
    //If there is no winner, return false
    // Even it's a tie, it should be checked in the main
    return false;
}

//Q4
void computerMove(char board[]){
    // Computer first check if there is a position it can win
    // I use a loop to try every position except already occupied
    // from board[0] to board[26], computer first try to move to this position
    // to see if it can win
    for(int i = 0; i<27; i++){
        if(board[i] != 'O' && board[i] != 'X'){
            char temp = board[i];
            board[i] = 'O';
            if(checkWinner(board)){
                return;
            } else{
                board[i] = temp;
            }
        }
    }
    // If there is no such a position, just try all positions that player can move
    // If player can win, just block it
    for(int i = 0; i<27; i++){
        if(board[i] != 'O' && board[i] != 'X'){
            char temp = board[i];
            board[i] = 'X';
            if(checkWinner(board)){
                board[i] = 'O';
                return;
            } else{
                board[i] = temp;
            }
        }
    }
    // If no such a position, computer just move to first not occupied position
    // since random is not required
    for(int i = 0; i<27; i++){
        if(board[i] != 'O' && board[i] != 'X'){
            board[i] = 'O';
            return;
        }
    }
}

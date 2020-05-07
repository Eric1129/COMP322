/**
 * Following code is for COMP322 A1
 * Created by Eric Shen on 2020/1/29.
 * 260798146
 */

// This is my helper header file

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

    void greetAndInstruct();
    void displayBoard (char board[]);
    bool checkIfLegal (int cellNbre, char board[]);
    bool checkWinner(char board[]);
    void computerMove(char board[]);

#endif

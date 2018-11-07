#include <iostream>
#include <string>

using namespace std;

//This function initialises a 9x9 grid.
//The extra row,col pair is for adding the enumeration of the board
void initializeBoard(char board[][9]) {
    for (int r = 0; r < 9; r++) {
        if (r % 2 == 0) {
            for (int c = 0; c < 9; c++) {
                if (c % 2 == 0) {
                    board[r][c] = '=';
                } else {
                    board[r][c] = ' ';
                }
            }
        } else {
            for (int c = 0; c < 9; c++) {
                if (c % 2 == 0) {
                    board[r][c] = ' ';
                } else {
                    board[r][c] = '=';
                }
            }
        }
    }
    
    //Fills the board with the 0 player
    for (int r = 1; r < 4; r++) {
        if (r % 2 != 0) {
            for (int c = 2; c < 9; c+=2) {
                board[r][c] = '0';
            }
        } else {
            for (int c = 1; c < 9; c+=2) {
                board[r][c] = '0';
            }
        }
    }
    
    //Fills the board with the X player
    for (int r = 6; r < 9; r++) {
        if (r % 2 != 0) {
            for (int c = 2; c < 9; c+=2) {
                board[r][c] = 'X';
            }
        } else {
            for (int c = 1; c < 9; c+=2) {
                board[r][c] = 'X';
            }
        }
    }
}

//This function prints the board on the console
void printBoard(char board[][9]) {
    int nV = 1;
    int nH = 1;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            //This is just to skip the point [0,0] which doesn't include anything.
            if (r == 0 && c == 0) {
                //Visual enhancement purpose ONLY!
                cout << "   ";
                continue;
            }
            if (r == 0) {
                //Visual enhancement purpose ONLY!
                cout << "  " << nV << " ";
                nV++;
            } else if (c == 0) {
                //Visual enhancement purpose ONLY!
                cout << "  " << nH << " ";
                nH++;
            } else {
                cout << '[' << board[r][c] << ']' << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    char board[9][9];
    initializeBoard(board);
    printBoard(board);
}

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
                board[r][c] = 'O';
            }
        } else {
            for (int c = 1; c < 9; c+=2) {
                board[r][c] = 'O';
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

//Function thatt verifies input is valid. Meaning not OOB.
bool checkIfMoveValid(char board[][9], char player, int r, int c) {
    /*If player's input is OOB, the function instantly returns true
     with a rejection message indicating that the checkbox selected is OOB.
     */
    if (r > 8 || r < 1 || c > 8 || c < 1) {
        cout << "OOB! [1-8][1-8][L-R]" << endl;
        cout << "ENTER VALID VALUES:" << endl;
        return true;
    }
    
    /*If player input coordinate does not match the player's value,
     it returns true right away with a rejection message indicating
     that the checkbox selected is not changeable by the current player.
     */
    if (board[r][c] != player) {
        cout << "Whoops! It seems that you don't have a piece there." << endl;
        cout << "PICK A BOX THAT CONTAINS A PIECE OF YOURS:" << endl;
        return true;
    }
    
    return false;
}

//This function verifies if the player would like to continue playing. It starts asking after the FIRST move.
//User can input 'Y' or 'N' upper and lower case
bool checkIfKeepPlaying(char keepPlaying) {
    if (toupper(keepPlaying) == 'Y') {
        return false;
    }
    return true;
}

//Verifies that the updated position is possible and inside the board.
bool checkIfInside(int r, int c) {
    if (r > 8 || r < 1 || c > 8 || c < 1) {
        return false;
    }
    return true;
}

/*
 This function verifies if the move that is taking place does not land OB or on top of another piece of equal
 colour. There is additionally another function "checkIfInside()" that is called with the row and column updated
 to verify that the move is possible.
 */
bool checkIfMovePossible(char board[][9], char player, int r, int c) {
    if ((board[r][c] == ' ' || board[r][c] != player) && checkIfInside(r, c)) {
        return true;
    }
    return false;
}

bool checkIfTakePiece(char board[][9], char player, int r, int c, char dir, int vDisp, int hDisp) {
    if ((board[r][c] != player && board[r][c] != ' ') && board[r + vDisp][c + hDisp] == ' ') {
        return true;
    }
    return false;
}

void movePiece(char board[][9], char &player, int &r, int &c, char &dir, int &totalMoves, char &keepPlaying) {
    do {
        if (totalMoves != 0) {
            cout << "Continue playing? (Y/N): ";
            cin >> keepPlaying;
            if (checkIfKeepPlaying(keepPlaying)) {
                return;
            }
        }
        //Determines whose turn is and if move is valid.
        (player == 'X') ? cout << "Player X row -> " : cout << "Player Y row -> ";
        cin >> r;
        cout << "column -> ";
        cin >> c;
        cout << "direction (R - right, L - left) -> ";
        cin >> dir;
    } while (checkIfMoveValid(board, player, r, c));
    
    /*
     Here is where the magic happens. Once a move is verified and valid, the following
     code changes the values of the checkboxes accordingly. It changes the value of
     the original box the piece was located at for an empty space and targets the moving
     checkbox the piece should move to.
     */
    //Determines whose piece will move.
    if (player == 'X') {
        //Determines the direction of that piece movement.
        if (toupper(dir) == 'R') {
            //MAGICAL CHANGE
            if (checkIfMovePossible(board, player, r - 1, c + 1)) {
                //if move is possible, then check if you have any piece to eat.
                //if yes, eat it, if not, do the following >>>>>>
                if (checkIfTakePiece(board, player, r - 1, c + 1, dir, -1, 1)) {
                    board[r][c] = ' ';
                    board[r - 1][c + 1] = ' ';
                    board[r - 2][c + 2] = 'X';
                } else {
                    board[r][c] = ' ';
                    board[r - 1][c + 1] = 'X';
                }
            }
            player = 'O';
            totalMoves++;
        } else {
            //MAGICAL CHANGE
            if (checkIfMovePossible(board, player, r - 1, c - 1)) {
                if (checkIfTakePiece(board, player, r - 1, c - 1, dir, -1, -1)) {
                    board[r][c] = ' ';
                    board[r - 1][c - 1] = ' ';
                    board[r - 2][c - 2] = 'X';
                } else {
                    board[r][c] = ' ';
                    board[r - 1][c - 1] = 'X';
                }
            }
            player = 'O';
            totalMoves++;
        }
    } else {
        //Determines the direction of that piece movement.
        if (toupper(dir) == 'R') {
            //MAGICAL CHANGE
            if (checkIfMovePossible(board, player, r + 1, c + 1)) {
                if (checkIfTakePiece(board, player, r + 1, c + 1, dir, 1, 1)) {
                    board[r][c] = ' ';
                    board[r + 1][c + 1] = ' ';
                    board[r + 2][c + 2] = 'O';
                } else {
                    board[r][c] = ' ';
                    board[r+1][c+1] = 'O';
                }
            }
            player = 'X';
            totalMoves++;
        } else {
            //MAGICAL CHANGE
            if (checkIfMovePossible(board, player, r + 1, c - 1)) {
                if (checkIfTakePiece(board, player, r + 1, c - 1, dir, 1, -1)) {
                    board[r][c] = ' ';
                    board[r + 1][c - 1] = ' ';
                    board[r + 2][c - 2] = 'O';
                } else {
                    board[r][c] = ' ';
                    board[r+1][c-1] = 'O';
                }
            }
            player = 'X';
            totalMoves++;
        }
    }
}

int main() {
    int r, c, totalMoves = 0;
    char board[9][9], player = 'X', dir, keepPlaying = 'Y';
    
    initializeBoard(board);
    printBoard(board);
    
    while (!checkIfKeepPlaying(keepPlaying)) {
        movePiece(board, player, r, c, dir, totalMoves, keepPlaying);
        printBoard(board);
    }
}


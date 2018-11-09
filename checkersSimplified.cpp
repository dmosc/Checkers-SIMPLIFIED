//Currently working on the moveTesting branch **********
#include <iostream>
#include <string>

using namespace std;

void printResult(int scoreCard) {
    if (scoreCard == 0) {
        cout << "It was a tie!" << endl;
    } else if (scoreCard > 0) {
        cout << "X player won!" << endl;
    } else {
        cout << "O player won!" << endl;
    }
}

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
bool moveValid(char board[][9], char player, int r, int c) {
    /*If player's input is OOB, the function instantly returns true
     with a rejection message indicating that the checkbox selected is OOB.
     */
    if (r > 8 || r < 1 || c > 8 || c < 1) {
        cout << "OOB! [1-8][1-8][L-R]" << endl;
        cout << "ENTER VALID VALUES:" << endl;
        return false;
    }
    
    /*If player input coordinate does not match the player's value,
     it returns true right away with a rejection message indicating
     that the checkbox selected is not changeable by the current player.
     */
    if (board[r][c] != player) {
        cout << "Whoops! It seems that you don't have a piece there." << endl;
        cout << "PICK A BOX THAT CONTAINS A PIECE OF YOURS:" << endl;
        return false;
    }
    
    return true;
}

//This function verifies if the player would like to continue playing. It starts asking after the FIRST move.
//User can input 'Y' or 'N' upper and lower case
bool checkIfKeepPlaying(char &keepPlaying, int &totalMoves) {
    if (totalMoves != 0) {
        cout << "Continue playing? (Y/N): ";
        cin >> keepPlaying;
        if (toupper(keepPlaying) == 'N') {
            return false;
        }
    }
    return true;
}

void inputValues(char board[][9], char &player, int &r, int &c, char &dir) {
    (player == 'X') ? cout << "Player X row -> " : cout << "Player O row -> ";
    cin >> r;
    cout << "column -> ";
    cin >> c;
    cout << "direction (R - right, L - left) -> ";
    cin >> dir;
}

//Verifies that the updated position is possible and inside the board.
bool checkIfInside(int r, int c) {
    if (r > 8 || r < 1 || c > 8 || c < 1) {
        return false;
    }
    return true;
}

/////////////////////////////////////////// X FUNCTIONS
bool movePossibleX(char board[][9], int r, int c) {
    if (board[r][c] == ' ' && checkIfInside(r, c)) {
        return true;
    }
    return false;
}

bool takePossibleX(char board[][9], int r, int c, int r1, int c1) {
    if (board[r][c] == 'O' && board[r1][c1] == ' ' && checkIfInside(r1, c1)) {
        return true;
    }
    return false;
}

/*
 This function verifies if the move that is taking place is capable of taking a piece of the other player,
 thus, enabling piece eating between players.
 */

void moveXR(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r - 1][c + 1] = 'X';
}

void moveXL(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r - 1][c - 1] = 'X';
}

void takePieceXR(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r - 1][c + 1] = ' ';
    board[r - 2][c + 2] = 'X';
}

void takePieceXL(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r - 1][c - 1] = ' ';
    board[r - 2][c - 2] = 'X';
}

/////////////////////////////////////////// O FUNCTIONS
bool movePossibleO(char board[][9], int r, int c) {
    if (board[r][c] == ' ' && checkIfInside(r, c)) {
        return true;
    }
    return false;
}

bool takePossibleO(char board[][9], int r, int c, int r1, int c1) {
    if (board[r][c] == 'X' && board[r1][c1] == ' ' && checkIfInside(r1, c1)) {
        return true;
    }
    return false;
}

void moveOR(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r + 1][c + 1] = 'O';
}

void moveOL(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r + 1][c - 1] = 'O';
}

void takePieceOR(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r + 1][c + 1] = ' ';
    board[r + 2][c + 2] = 'O';
}

void takePieceOL(char board[][9], int r, int c) {
    board[r][c] = ' ';
    board[r + 1][c - 1] = ' ';
    board[r + 2][c - 2] = 'O';
}

void movePiece(char board[][9], char &player, int &r, int &c, char &dir, int &totalMoves, char &keepPlaying, int &scoreCard) {
    do {
        //Determines whose turn is and if move is valid.
        inputValues(board, player, r, c, dir);
    } while (!moveValid(board, player, r, c));
    
    /*
     Here is where the magic happens. Once a move is verified and valid, the following
     code changes the values of the checkboxes accordingly. It changes the value of
     the original box the piece was located at for an empty space and targets the moving
     checkbox the piece should move to.
     */
    //Determines whose piece will move.
    if (player == 'X') {
        if (toupper(dir) == 'R') {
            if (movePossibleX(board, r - 1, c + 1)) {
                moveXR(board, r, c);
            } else if (takePossibleX(board, r - 1, c + 1, r - 2, c + 2)) {
                takePieceXR(board, r, c);
                scoreCard++;
            }
        } else {
            if (movePossibleX(board, r - 1, c - 1)) {
                moveXL(board, r, c);
            } else if (takePossibleX(board, r - 1, c - 1, r - 2, c - 2)) {
                takePieceXL(board, r, c);
                scoreCard++;
            }
        }
        player = 'O';
        totalMoves++;
    } else {
        if (toupper(dir) == 'R') {
            if (movePossibleO(board, r + 1, c + 1)) {
                moveOR(board, r, c);
            } else if (takePossibleO(board, r + 1, c + 1, r + 2, c + 2)) {
                takePieceOR(board, r, c);
                scoreCard--;
            }
        } else {
            if (movePossibleO(board, r + 1, c - 1)) {
                moveOL(board, r, c);
            } else if (takePossibleO(board, r + 1, c - 1, r + 2, c - 2)) {
                takePieceOL(board, r, c);
                scoreCard--;
            }
        }
        player = 'X';
        totalMoves++;
    }
}

int main() {
    int r, c, totalMoves = 0, scoreCard = 0;
    char board[9][9], player = 'X', dir, keepPlaying = 'Y';
    
    initializeBoard(board);
    printBoard(board);
    
    while (checkIfKeepPlaying(keepPlaying, totalMoves)) {
        movePiece(board, player, r, c, dir, totalMoves, keepPlaying, scoreCard);
        printBoard(board);
    }
    
    printResult(scoreCard);
}




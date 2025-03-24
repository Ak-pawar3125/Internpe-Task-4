#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

vector<vector<char>> board(ROWS, vector<char>(COLS, EMPTY));
bool player1Turn = true;


void displayBoard() {
    cout << "\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "-----------------------------\n";
    cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
    cout << "-----------------------------\n";
}


bool isValidMove(int col) {
    return col >= 0 && col < COLS && board[0][col] == EMPTY;
}


void makeMove(int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            break;
        }
    }
}


bool checkWinner(char player) {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (j + 3 < COLS && board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) 
                return true;
            if (i + 3 < ROWS && board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) 
                return true;
            if (i + 3 < ROWS && j + 3 < COLS && board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) 
                return true;
            if (i + 3 < ROWS && j - 3 >= 0 && board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) 
                return true;
        }
    }
    return false;
}


bool isBoardFull() {
    for (int j = 0; j < COLS; ++j) {
        if (board[0][j] == EMPTY)
            return false;
    }
    return true;
}

void resetGame() {
    board.assign(ROWS, vector<char>(COLS, EMPTY));
    player1Turn = true;
}

int main() {
    while (true) {
        displayBoard();
        char currentPlayer = (player1Turn) ? PLAYER1 : PLAYER2;
        cout << "Player " << currentPlayer << ", enter your move (1-7): ";
        
        int col;
        cin >> col;
        col--;
        
        if (!isValidMove(col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        makeMove(col, currentPlayer);
        
        if (checkWinner(currentPlayer)) {
            displayBoard();
            cout << "Congratulations! Player " << currentPlayer << " wins!\n";
            break;
        }
        
        if (isBoardFull()) {
            displayBoard();
            cout << "It's a tie!\n";
            break;
        }
        
        player1Turn = !player1Turn;
    }
    
    cout << "Do you want to play again? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        resetGame();
        main(); 
    }
    return 0;
}

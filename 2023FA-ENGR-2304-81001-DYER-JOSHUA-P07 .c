/*

2023FA-ENGR-2304-81001-DYER-JOSHUA-P07

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to print the Tic Tac Toe board
void print_board(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Function to initialize the board with empty spaces
void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to check if the game has been won or tied
int check_game_result(char board[3][3], char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1; // Row
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1; // Column
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1; // Diagonal
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1; // Diagonal

    // Check for a tie
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0; // Game still ongoing
        }
    }

    return -1; // Game is a tie
}

// Function to make a move for a human player
void human_move(char board[3][3], char player) {
    int row, col;
    printf("Player %c, enter your move (row and column, e.g., 1 1): ", player);
    scanf("%d %d", &row, &col);

    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        printf("Invalid move. Try again.\n");
        human_move(board, player);
    } else {
        board[row - 1][col - 1] = player;
    }
}

// Function to make a random move for the computer player
void computer_move(char board[3][3], char player) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    board[row][col] = player;
}

int main() {
    char board[3][3];
    char players[2] = { 'X', 'O' };

    srand(time(NULL)); // Seed the random number generator with the current time

    int numPlayers;
    printf("Welcome to Tic Tac Toe!\n");
    printf("Choose the number of players (1 or 2): ");
    scanf("%d", &numPlayers);

    if (numPlayers != 1 && numPlayers != 2) {
        printf("Invalid number of players. Please choose 1 or 2.\n");
        return 1;
    }

    initialize_board(board);
    int currentPlayer = rand() % 2; // Randomly select the starting player

    printf("Player 1: X, Player 2: O\n");
    print_board(board);

    int game_result;

    while (1) {
        if (currentPlayer == 0) {
            if (numPlayers == 1) {
                computer_move(board, players[currentPlayer]);
            } else {
                human_move(board, players[currentPlayer]);
            }
        } else {
            human_move(board, players[currentPlayer]);
        }

        print_board(board);

        game_result = check_game_result(board, players[currentPlayer]);

        if (game_result == 1) {
            printf("Player %c wins!\n", players[currentPlayer]);
            break;
        } else if (game_result == -1) {
            printf("It's a tie!\n");
            break;
        }

        currentPlayer = (currentPlayer + 1) % 2;
    }

    return 0;
}




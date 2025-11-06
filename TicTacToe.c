// package for the tic-tac-toe program.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Functions for TicTacToe
// 1. This function takes an array of 10 characters as input and prints out the Tic-Tac-Toe board using ASCII characters.
void drawBoard(char board[]);
// 2. This function prompts the user to choose between 'X' and 'O' and returns the corresponding integer value (1 for 'X' and 0 for 'O').
int inputPlayerLetter();
// 3. This function randomly selects the player who goes first and returns 'p' for player or 'c' for computer.
char whoGoesFirst();
// 4. This function prompts the user to play again or quit and returns 1 for 'Yes' and 0 for 'No'.
int playAgain();
// 5. This function takes an array of 10 characters, a player's letter ('X' or 'O'), and the move the player wants to make (1-9) as input and updates the board accordingly.
void makeMove(char board[], char letter, int move);
// 6. This function checks whether the specified player has won and returns 1 if they have and 0 otherwise.
int isWinner(char board[], char letter);
// 7. This function checks whether a space on the board is free and returns 1 if it is and 0 otherwise.
int isSpaceFree(char board[], int move);
// 8. This function prompts the player to enter their move and returns the integer value of the move.
int getPlayerMove(char board[]);
// 9. This function takes an array of 10 characters, an array of valid moves, and the size
int chooseRandomMoveFromList(char board[], int movesList[], int size);
// 10. Gets computer moves
int getComputerMove(char board[], char computerLetter);
// 11. Checks whether the board is empty
int isBoardFull(char board[]);


int main()
{
    // Set the random seed
    srand(time(NULL));

    // Main game loop 
    do {
        char board[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        int player = inputPlayerLetter(); // player input
        char playerLetter = (player == 1) ? 'X' : 'O';
        char computerLetter = (player == 1) ? 'O' : 'X';
        char turn = whoGoesFirst(); // random turn
        printf("\n%s will go first.\n", (turn == 'p') ? "Player" : "Computer"); //show who will go first

        //Check if player wins or computer
        //Check for tie
        while (!isWinner(board, playerLetter) && !isWinner(board, computerLetter) && !isBoardFull(board)) {
            if (turn == 'p') {
                drawBoard(board);
                int move = getPlayerMove(board);
                makeMove(board, playerLetter, move);
                turn = 'c';
            } 
            else {
                int move = getComputerMove(board, computerLetter);
                makeMove(board, computerLetter, move);
                turn = 'p';
            }
        }

        //Show the status
        drawBoard(board);
        if (isWinner(board, playerLetter)) {
            printf("Congratulations! You have won the game!\n");
        } else if (isWinner(board, computerLetter)) {
            printf("The computer has beaten you! You lose.\n");
        } else {
            printf("The game is a tie!\n");
        }
    }
    while (playAgain());

    printf("\nThanks for playing!\n");
    return 0;
}


//Function of drawBoard
//This function prints out the board that it was passed.
//"board" is a list of 10 strings representing the board (ignore index 0)
void drawBoard(char board[])
{
    printf("   |   |\n");
    printf(" %c | %c | %c\n", board[7], board[8], board[9]);
    printf("   |   |\n");
    printf("---|---|---\n");
    printf("   |   |\n");
    printf(" %c | %c | %c\n", board[4], board[5], board[6]);
    printf("   |   |\n");
    printf("---|---|---\n");
    printf("   |   |\n");
    printf(" %c | %c | %c\n", board[1], board[2], board[3]);
    printf("   |   |\n");
}


int inputPlayerLetter(){
    // Lets the player choose a letter
    char letter = ' ';
    while (letter != 'X' && letter != 'O')
    {
        printf("\nDo you want to be X or O? : ");
        scanf("%c", &letter);
        letter = toupper(letter);
    } 
    // Return with the computer other letter then player's letter
    return (letter == 'X') ? 1 : 0;
}

char whoGoesFirst() {
    // Randomly choose the player who goes first.
    if (rand() % 2 == 0)
    { return 'c'; }
    else
    { return 'p';}
}

int playAgain() {
    // This function returns True if the player wants to play again, otherwise it returns False
    char answer = ' ';
    while (answer != 'Y' && answer != 'N') {
        printf("\nDo you want to play again? (Y/N) : ");
        scanf("%c", &answer);
        answer = toupper(answer);
    }
    
    if (answer == 'Y') {
        return 1; // 1 for True
    } 
    else {
        return 0; // 0 for False
    }
}

void makeMove(char board[], char letter, int move){
    board[move] = letter;
}

int isWinner(char board[], char le) {
    // Given a board and a player's letter, this function returns True if that player has won.
    return ((board[7] == le && board[8] == le && board[9] == le) || // across the top
            (board[4] == le && board[5] == le && board[6] == le) || // across the middle
            (board[1] == le && board[2] == le && board[3] == le) || // across the bottom
            (board[7] == le && board[4] == le && board[1] == le) || // down the left side
            (board[8] == le && board[5] == le && board[2] == le) || // down the middle
            (board[9] == le && board[6] == le && board[3] == le) || // down the right side
            (board[7] == le && board[5] == le && board[3] == le) || // diagonal
            (board[9] == le && board[5] == le && board[1] == le)); // diagonal
}

int isSpaceFree(char board[], int move) {
    //Return true if the passed move is free on the passed board.
    return board[move] == ' ';
}

int getPlayerMove(char board[]) {
    // Let the player type in his move.
    int move;
    while (1) {
        printf("\nWhat is your next move? (1-9) : ");
        scanf("%d", &move);
        if (move >= 1 && move <= 9 && isSpaceFree(board, move))
            break;
    }
    return move;
}

int chooseRandomMoveFromList(char board[], int movesList[], int Size) {
// Returns a valid move from the passed list on the passed board.
// Returns -1 if there is no valid move.
    int possibleMoves[9];
    int possibleMovesSize = 0;
    for (int i = 0; i < Size; i++) {
        if (isSpaceFree(board, movesList[i]))
        {
            possibleMoves[possibleMovesSize] = movesList[i];
            possibleMovesSize++;
        }
    }
    if (possibleMovesSize != 0)
    {
        int randomIndex = rand() % possibleMovesSize;
        return possibleMoves[randomIndex];
    } 
    else { return -1; }
}


int getComputerMove(char board[], char computerLetter) {
    // Given a board and the computer's letter, determine where to move and return that move.
    char playerLetter = (computerLetter == 'X') ? 'O' : 'X';
    // Here is our algorithm for our Tic Tac Toe AI:
    // First, check if we can win in the next move
    for (int i = 1; i <= 9; i++) {
        char copy[10];
        for (int j = 1; j <= 9; j++) {
            copy[j] = board[j];
        }
        if (isSpaceFree(copy, i)) {
            makeMove(copy, computerLetter, i);
            if (isWinner(copy, computerLetter)) {
                return i;
            }
        }
    }

    // Check if the player could win on his next move, and block them.
    for (int i = 1; i <= 9; i++) {
        char copy[10];
        for (int j = 1; j <= 9; j++) {
            copy[j] = board[j];
        }
        if (isSpaceFree(copy, i)) {
            makeMove(copy, playerLetter, i);
            if (isWinner(copy, playerLetter)) {
                return i;
            }
        }
    }

    // Try to take one of the corners, if they are free.
    int move = chooseRandomMoveFromList(board, (int[]){1, 3, 7, 9}, 4);
    if (move != -1) {
        return move;
    }

    // Try to take the center, if it is free.
    if (isSpaceFree(board, 5)) {
        return 5;
    }

    // Move on one of the sides.
    move = chooseRandomMoveFromList(board, (int[]){2, 4, 6, 8}, 4);
    if (move != -1) {
        return move;
    }

    return -1; // No valid move found
}

int isBoardFull(char board[]) {
    // Return True if every space on the board has been taken. Otherwise return False.
    for (int i = 1; i <= 9; i++) {
        if (isSpaceFree(board, i)) {
            return 0;
        }
    }
    return 1;
}

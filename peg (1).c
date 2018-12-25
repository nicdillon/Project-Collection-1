
/* Program that determines the number of possible legal moves in a given
   position of Peg.

   Author: Nic Dillon
*/

#include <stdio.h>

#define BOARD_SIZE 7

/* Returns the number of possible moves for a given peg.

  Parameters:
      board - a 7x7 char array representing the current state of the board.
              Pieces are denoted by 'o' and empty squares are denoted by '.'
      row - an int representing the row in which the current peg is located
      column - an int representing the column in which the curreng peg is
               located

  Returns:
      possibleMoves - an int representing the possible number of pegMoves
                      for the given peg
*/
int pegMoves(char board[BOARD_SIZE][BOARD_SIZE], int row, int column) {
  int possibleMoves = 0;
  // Iterates over all relevent spaces and determines if current peg
  // could jump to said space
  for(int r = -1; r <= 1; r++) {
    if((row < 2  && r == -1) || (row > 4 && r == 1)) {
      continue;
    }
    for(int c = -1; c <= 1; c++) {
      if((r != 0 && c != 0) || (r == 0 && c == 0) || (column < 2 && c == -1)
      || (column > 4 && c ==1)) {
        continue;
      }
      if((board[row + 2 * r][column + 2 * c] == '.')
      && (board[row + r][column + c] == 'o')) {
        possibleMoves++;
      }
    }
  }
  return possibleMoves;
}

/* Returns the total number of legal moves that can be made from a given
   position in Peg.

   Parameters:
       board - a 7x7 char array representing the current state of the board.
               Pieces are denoted by 'o' and empty squares are denoted by '.'

   Returns:
       The number of moves that a player can make in the given position.
*/
int countLegalMoves(char board[BOARD_SIZE][BOARD_SIZE]) {
    int legalMoves = 0;
    for(int i=0; i < BOARD_SIZE; i++) {
      for(int j=0; j < BOARD_SIZE; j++) {
        if(((i < 2 || i > 4) && (j < 2 || j > 4)) || (board[i][j] == '.')) {
          continue;
        }
        legalMoves += pegMoves(board, i, j);
      }
    }
    return legalMoves;
}

/* Tester function. */
int main() {
    char board1[BOARD_SIZE][BOARD_SIZE] = {"  ooo  ",
                                           "  ooo  ",
                                           "ooooooo",
                                           "ooo.ooo",
                                           "ooooooo",
                                           "  ooo  ",
                                           "  ooo  "};
    printf("%d\n", countLegalMoves(board1));  // 4

    char board2[BOARD_SIZE][BOARD_SIZE] = {"  ooo  ",
                                           "  ooo  ",
                                           "..ooo..",
                                           "oo...oo",
                                           "..ooo..",
                                           "  ooo  ",
                                           "  ooo  "};
    printf("%d\n", countLegalMoves(board2));  // 12

    return 0;
}

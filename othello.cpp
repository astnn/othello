#include <cstdint> // Supplies uint#_t formats
#include <iostream> // Supplies std::cout ect.

#include "othello.h"

using namespace std;

/*Othello: Constructor that set game start values */
Othello::Othello() {
  // Reset board to start conditions
  for (uint8_t i = 0; i < BOARDLEN; i++) {
    for (uint8_t j = 0; j < BOARDLEN; j++) {
      board[i][j] = EMPTYSYMB;
    }
  }
  board[3][3] = 'W';
  board[3][4] = 'B';
  board[4][3] = 'B';
  board[4][4] = 'W';
  
  // Set starting player to black
  currPlayer = 'B';
  
  // Defualt ai off
  ai = false;
}

void Othello::setAiBlack(void) {
  aiColour = 'B';
}

void Othello::setAiWhite(void) {
  aiColour = 'W';
}

void Othello::turnAiOn(void) {
  ai = true;
}

bool Othello::isAi(void) {
  return ai;
}

bool Othello::isAiTurn(void) {
  return currPlayer == aiColour;
}

char Othello::getCurrPlayer(void) {
  return currPlayer;
}

/* switchCurrPlayer: Siwtches the currently active player/colour */
void Othello::switchCurrPlayer(void) {
  currPlayer = (currPlayer == 'B' ? 'W' : 'B');
}

/* isFlipDir: Checks if the specified direction would result in any pieces
  being flipped. (row,col) is the position where a piece would be placed,
  (dRow,dCol) is the direction of checking */
bool Othello::isFlipDir(uint8_t row, uint8_t col, int8_t dRow, int8_t dCol, char colour) {
  // Rough pseudocode:
  // Run in direction given.
  // Continue while oposing colour is met
  // Return sucess if own colour is met, else failure at end of board or empty
  //    piece
  
  char oppColour = (colour == 'B') ? 'W' : 'B';
  
  row += dRow;
  col += dCol;
  
  if (row >=  BOARDLEN || col >= BOARDLEN) {
    return false;
  }
  
  if (board[row][col] == oppColour) {
    while (row < BOARDLEN && col < BOARDLEN) {
      if (board[row][col] == colour) {
        return true;
      } else if (board[row][col] == EMPTYSYMB) {
        return false;
      }
      row += dRow;
      col += dCol;
    }
  }
  
  return false;
}

/* flipDir: Flips pieces from position (row,col) (the position excluded) in
direction (dRow,dCol) until colour is encountered. Assumes validity of flip
has been checked with isFlipDir */
void Othello::flipDir(uint8_t row, uint8_t col, int8_t dRow, int8_t dCol, char colour) {
  row += dRow;
  col += dCol;
  
  while (board[row][col] != colour) {
    board[row][col] = colour;
    row += dRow;
    col += dCol;
  }
}

/* isValidMove: Chekcs if placing a piece on the specified location is valid */
bool Othello::isValidMove(uint8_t row, uint8_t col, char colour) {
  // Pseudocode:
  // Is position on board?
  // Is position empty?
  // Would it cause a flip in any direction?
  
  
  if (row >= BOARDLEN || col >= BOARDLEN ) {
    return false;
  } else if (board[row][col] != EMPTYSYMB) {
    return false;
  }
  
  // Check all 8 directions for flips
  if ( isFlipDir(row, col, -1, 0, colour) ) {          // N
    return true;
  } else if ( isFlipDir(row, col, -1, 1, colour) ) { // NE
    return true;
  } else if ( isFlipDir(row, col, 0, 1, colour) ) {   // E
    return true;
  } else if ( isFlipDir(row, col, 1, 1, colour) ) { // SE
    return true;
  } else if ( isFlipDir(row, col, 1, 0, colour) ) {   // S
    return true;
  } else if ( isFlipDir(row, col, 1, -1, colour) ) { // SW
    return true;
  } else if ( isFlipDir(row, col, 0, -1, colour) ) {   // W
    return true;
  } else if ( isFlipDir(row, col, -1, -1, colour) ) { // NW
    return true;
  }
  
  return false;
}

/* makeMove: Places piece of given colour at position (row,dir), flips the
affected pieces, and switch the current player.
Assumes validity of move have been checked with isValidMove */
void Othello::makeMove(uint8_t row, uint8_t col, char colour) {
  board[row][col] = colour;
  
  // Check all 8 directions for flip, and apply where valid
  if ( isFlipDir(row, col, -1, 0, colour) ) {    // N
    flipDir(row, col, -1, 0, colour);
  }
  if ( isFlipDir(row, col, -1, 1, colour) ) {  // NE
    flipDir(row, col, -1, 1, colour);
  }
  if ( isFlipDir(row, col, 0, 1, colour) ) {    // E
    flipDir(row, col, 0, 1, colour);
  }
  if ( isFlipDir(row, col, 1, 1, colour) ) {  // SE
    flipDir(row, col, 1, 1, colour);
  }
  if ( isFlipDir(row, col, 1, 0, colour) ) {    // S
    flipDir(row, col, 1, 0, colour);
  }
  if ( isFlipDir(row, col, 1, -1, colour) ) {  // SW
    flipDir(row, col, 1, -1, colour);
  }
  if ( isFlipDir(row, col, 0, -1, colour) ) {    // W
    flipDir(row, col, 0, -1, colour);
  }
  if ( isFlipDir(row, col, -1, -1, colour) ) {  // NW
    flipDir(row, col, -1, -1, colour);
  }
  
  currPlayer = (currPlayer == 'B' ? 'W' : 'B');
  
  return;
}

/* hasMove: Checks if colour has any valid moves to make. Exits at first valid
move */
bool Othello::hasMove(char colour) {
  for( uint8_t row = 0; row < BOARDLEN; row++) {
    for (uint8_t col = 0; col < BOARDLEN; col++) {
      if (board[row][col] == EMPTYSYMB ) {
        if (isValidMove(row, col, colour))  {
          return true;
        }
      }
    }
  }
  
  return false;
}

/* calcPossMoves: Calculate all possible moves for the given colour and place
them into possibleMoves-struct. Returns no. of poss moves. */
uint8_t Othello::calcPossMoves(char colour) {
  uint8_t i = 0;
  
  for( uint8_t row = 0; row < BOARDLEN; row++) {
    for (uint8_t col = 0; col < BOARDLEN; col++) {
      if (board[row][col] == EMPTYSYMB ) {
        if (isValidMove(row, col, colour))  {
          possibleMoves.row[i] = row;
          possibleMoves.col[i] = col;
          i++;
        }
      }
    }
  }
  
  return i;
}

/* isGameOver: Returns true if neither player has any possible moves left */
bool Othello::isGameOver(void) {    
  char oppPlayer = (currPlayer == 'B' ? 'W' : 'B');
  
  return !hasMove(currPlayer) && !hasMove(oppPlayer);
}

/* mustPass: Check if the current player must pass the turn */
bool Othello::mustPass(void) {
  return !hasMove(currPlayer);
}

/* makeAiMove: Calculate the next AI move and implements it. Very rough
  implementation. AI simply chooses the first valid position. */
void Othello::makeAiMove(void) {
  uint8_t nMoves;
  
  nMoves = calcPossMoves(aiColour);
  if (nMoves > 0) {
    makeMove(possibleMoves.row[0], possibleMoves.col[0], aiColour);
  }
  return;
}

/* calculateScore: Counts number of pieces of each colour on the board, and
  stores the result in the given pointers */
void Othello::calculateScore(uint8_t *bScore, uint8_t *wScore) {
  *bScore = *wScore = 0;
  
  for( uint8_t row = 0; row < BOARDLEN; row++) {
    for (uint8_t col = 0; col < BOARDLEN; col++) {
      if (board[row][col] == 'B' ) {
        (*bScore)++;
      } else if(board[row][col] == 'W' ) {
        (*wScore)++;
      }
    }
  }
  return;
}

/* declareResults: Prints each players score and declares the winner */
void Othello::declareResults(void) {
  uint8_t bScore, wScore;
  
  calculateScore(&bScore, &wScore);
  printf("Black has %d points, white has %d points.\n", bScore, wScore);
  if (bScore > wScore) {
    cout << "Black is the winner!\n";
  } else if (wScore > bScore) {
    cout << "White is the winner!\n";
  } else {
    cout << "The game is a draw!\n";
  }
  
  return;
}


/* printBoard: print board position */
void Othello::printBoard(void) {
  cout << "\n\n";
  cout << "\t   a  b  c  d  e  f  g  h\n";
  for (uint8_t i = 0; i < BOARDLEN; i++) {
    cout << "\t" << i+1 << "  ";
    for (uint8_t j = 0; j < BOARDLEN; j++) {
      cout << board[i][j] << "  ";
    }
    cout << i+1 << "\n";
  }
  cout << "\t   a  b  c  d  e  f  g  h\n";
  cout << "\n";
  
  return;
}

void Othello::printPassMessage(void) {
  if (currPlayer == 'B') {
    cout << "Black passed because there were no valid moves\n";
  } else {
    cout << "White passed because there were no valid moves\n";
  }
}

void Othello::printTurnMessage(void) {
  if (currPlayer == 'B') {
    cout << "Black's turn. Make a move: ";
  } else {
    cout << "White's turn. Make a move: ";
  }
}

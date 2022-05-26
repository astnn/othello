#ifndef _OTHELLO_H
#define _OTHELLO_H

#include <cstdint> // Supplies uint#_t formats

#define BOARDLEN 8
#define EMPTYSYMB '-'
#define MAXMOVES 60

using namespace std;

struct PossibleMoves {
  uint8_t row[MAXMOVES];
  uint8_t col[MAXMOVES];
};

class Othello {
  char board[BOARDLEN][BOARDLEN];
  char currPlayer;
  char aiColour;
  PossibleMoves possibleMoves;
  bool ai;

public:
  Othello(void);
  void setAiBlack(void);
  void setAiWhite(void);
  void turnAiOn(void);
  bool isAi(void);
  bool isAiTurn(void);
  char getCurrPlayer(void);
  void switchCurrPlayer(void);
  bool isValidMove(uint8_t row, uint8_t col, char colour);
  void makeMove(uint8_t row, uint8_t col, char colour);
  bool isGameOver(void);
  bool mustPass(void);
  void makeAiMove(void);
  void declareResults(void);
  void printBoard(void);
  void printPassMessage(void);
  void printTurnMessage(void);
  
  
private:
  bool isFlipDir(uint8_t row, uint8_t col, int8_t dRow, int8_t dCol, char colour);
  void flipDir(uint8_t row, uint8_t col, int8_t dRow, int8_t dCol, char colour);
  bool hasMove(char colour);
  uint8_t calcPossMoves(char colour);
  void calculateScore(uint8_t *bScore, uint8_t *wScore);
  
  

};
  
#endif /* _OTHELLO_H */

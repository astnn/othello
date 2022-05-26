#include <iostream> // Supplies std::cout ect.
#include <cctype> // Supplies isdigit, isalpha, tolower
#include <cstdint> // Supplies uint#_t formats
#include <string.h> // Supplies strncomp

#include "othello.h"

#define MAXINPUTLEN 10
#define ERR_AI_INP "Input not understood, please answer \"y\" if you wish " \
  "to play against the computer, or \"n\" if you wish to play two player: "
#define ERR_COL_INP "Input not understood, please answer \"B\" if you wish " \
  "to play black, or \"W\" if you wish to play white: ";
#define ERR_LOC_INV "The given location is not a valid move. Please enter " \
  "a valid location: "
#define ERR_INP_INV "Input invalid. Please specify a board location on the " \
  "form \"@#\",\nwhere @ is a letter between a and h, and # is a " \
  "number between 1 and 8: "  
  
/* function prototypes */
bool readAndValidateInput(char *s, uint8_t *prow, uint8_t *pcol);


int main(void) {
  uint8_t row;
  uint8_t col;
  char selection[MAXINPUTLEN];
  
  Othello game;
  
  // Chose between player oponent or AI
  cout << "Do you wish to play against the computer? [y/n]: ";
  while (true) {
    cin.getline(selection, MAXINPUTLEN);
    if ( strncmp(selection,"y",MAXINPUTLEN) == 0 ) {
      game.turnAiOn();
      break;
    } else if ( strncmp(selection,"n",MAXINPUTLEN) == 0 ) {
      break;
    }
    
    cout << ERR_AI_INP; 
  }
  
  // If against AI, chose player colour
  if (game.isAi()) {
    cout << "Please select your colour [B/W]: ";
    while (true) {
      cin.getline(selection, MAXINPUTLEN);
      if ( strncmp(selection,"W",MAXINPUTLEN) == 0 ) {
        game.setAiBlack();
        break;
      } else if ( strncmp(selection,"B",MAXINPUTLEN) == 0 ) {
        game.setAiWhite();
        break;
      }
      
      cout << ERR_COL_INP;
    }
  }
  
  // Run main game
  while(!game.isGameOver()) {
    if (game.mustPass()) {
      game.printPassMessage();
      game.switchCurrPlayer();
    }
    
    if (game.isAiTurn()) {
      game.makeAiMove();
    } else {
      game.printBoard();
      game.printTurnMessage();
      while(true) {
        cin.getline(selection, MAXINPUTLEN);
        if (readAndValidateInput(selection, &row, &col)) {
          if (game.isValidMove(row, col, game.getCurrPlayer())) {
            break;
          }
          cout << ERR_LOC_INV;
        } else {
          cout << ERR_INP_INV;
        }
      }
      game.makeMove(row, col, game.getCurrPlayer());
    }
  }
  
  game.printBoard();
  
  cout << "Game over!\n";
  game.declareResults();
  
  return 0;
}

bool readAndValidateInput(char *s, uint8_t *prow, uint8_t *pcol) {
  // Check alpha part
  int c = tolower(*s);
  if (c >= 'a' && c <= 'h') {
    *pcol = c - 'a';
  } else {
    return false;
  }
  
  // Check numeric part
  s++;
  if (*s >= '1' && *s <= '8') {
    *prow = *s - '0' - 1;
    return true;
  }
  return false;
}

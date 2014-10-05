#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "_2048no.h"


void setup() {
  // Initialyze matrix
  _matrix.begin();
  _matrix.setTextWrap(false);
  _matrix.setBrightness(40);
  _matrix.setTextColor( _matrix.Color(0, 255, 115) );
  
  // Initialyze random
  randomSeed(analogRead(0));

  // Calibration
  GYRO_CALIBRATION_X = analogRead(GYRO_X);
  GYRO_CALIBRATION_Y = analogRead(GYRO_Y);

  // Start the game
  startNewGame();
}

void loop() {
  Direction direction;

  // Get the player direction
  direction = checkGyroMove();
  switch (direction) {
    case Up:
      moveGridTo(0, 1, 4);
      printGrid();
      break;
    case Right:
      moveGridTo(3, 4, -1);
      printGrid();
      break;
    case Down:
      moveGridTo(12, 1, -4);
      printGrid();
      break;
    case Left:
      moveGridTo(0, 4, 1);
      printGrid();
      break;
    default: ;
  }
}

/**
 * Initialyze and reset everything to prepare a new game
 */
void startNewGame() {
  // Initialyze grid
  memset(_grid, 0, sizeof(_grid[0]) * 16);
  
  // Insert 2 number to start the game
  insertNumber();
  insertNumber();
  
  // Display the grid
  printGrid();

  _score = 0;
  playMelody(_startMelody, _startMelodyDurations, _startNotes);
}

/**
 * Function call on game over
 */
void gameOver() {
  String goText = "Game Over! ";
  String goScore = String(_score);
  int x = _matrix.width();
  int strLen;
  
  playMelody(_gameOverMelody, _gameOverMelodyDurations, _gameOverNotes);
  
  // Display game over message and score
  goText += goScore;
  strLen = goText.length() * 6;
  while (x > -strLen) {
    _matrix.fillScreen(0);
    _matrix.setCursor(x, 0);
    _matrix.print( goText );
    _matrix.show();
    delay(100);
    x--;
  }

  // Be prepare for the next game ! :)
  startNewGame();
}

/**
 * Manage the moving of the frames according a position and a direction given by the next row and frame
 */
void moveGridTo(int startPos, int nextRow, int nextFrame) {
  int pos, i, j;
  bool isGridMoved = false;

  // While we haven't move each row
  for (i = 0; i < 4; i++) {
      
    pos = startPos;
    _unmergeFrame = -1;
    // For the 3 next frame (the first one is obviously already placed to the limit)
    for (j = 0; j < 3; j++) {
      // Go to the next frame
      pos += nextFrame;
      if (moveFrame(pos, -nextFrame, startPos))
        isGridMoved = true;
    }

    // Go to the next row
    startPos += nextRow;
  }

  if (isGridMoved)
    insertNumber();

  if (checkGameOver())
    gameOver();
}

/**
 * Move a frame according to the nextFrame direction.
 * Retur True if the frame has moved, either false
 */
bool moveFrame(int pos, int nextFrame, int limit) {
  bool hasMoved = false;
  bool canMerge = true;

  while (pos != limit) {
    
    if ((_grid[pos] != 0) && (_grid[pos + nextFrame] == 0)) {
      _grid[pos + nextFrame] = _grid[pos];
      _grid[pos] = 0;
      hasMoved = true;
    }
    else if ((_grid[pos] != 0) && (_grid[pos] == _grid[pos + nextFrame]) && (canMerge) && ((pos + nextFrame) != _unmergeFrame)) {
      _grid[pos + nextFrame] = _grid[pos] * 2;
      _grid[pos] = 0;
      _score += _grid[pos + nextFrame];
      _unmergeFrame = pos + nextFrame;
      hasMoved = true;
      canMerge = false;
      playMelody(_combinationMelody, _combinationMelodyDurations, _combinationNotes);
    }
    else {
      break;
    }

    printGrid();
    delay(20);
    pos += nextFrame;
  }

  return (hasMoved);
}

#include "_2048no.h"

/**
 * Insert a new frame in the grid
 */
void insertNumber() {
  long index = random(16);
  long number = random(100);
  
  // Search a free grid frame. TODO: find a better way to do this
  while (_grid[index] != 0) {
    index = random(16);
  }
  
  // Determine the weight of the new frame. 66% chances to have a 2
  if (number < 66)
    _grid[index] = 2;
  else
    _grid[index] = 4;
}


/**
 *  Return the gyroscopic direction (if any), one of Direction enum
 */
Direction checkGyroMove() {
  int       vertical, horizontal, diffX, diffY;
  Direction currentDirection  = NoDirection;

  // Move detection
  horizontal = analogRead(GYRO_X);
  vertical = analogRead(GYRO_Y);

  // Calc the gap between the initial neutral position and the current inclination
  diffX = GYRO_CALIBRATION_X - horizontal;
  diffY = GYRO_CALIBRATION_Y - vertical;

  // Check if the joystick is bent to a direction
  if (_isDefaultPosition) {
    if ( (abs(diffX) > GYRO_DETECTION_GAP) || (abs(diffY) > GYRO_DETECTION_GAP) ) {
      _isDefaultPosition = false;
      if ( (abs(diffY) > GYRO_DETECTION_GAP) && (diffY < 0) )
        currentDirection = Down;
      else if ( (abs(diffY) > GYRO_DETECTION_GAP) && (diffY > 0) )
        currentDirection = Up;
      else if (diffX < 0)
        currentDirection = Left;
      else
        currentDirection = Right;
    }
  }
  // Else check if the joystick is back to its default position
  else if (!_isDefaultPosition) {
    horizontal = abs(horizontal - GYRO_CALIBRATION_X);
    vertical = abs(vertical - GYRO_CALIBRATION_Y);

    if ((vertical < MARGIN_DETECTION) && (horizontal < MARGIN_DETECTION)) {
      _isDefaultPosition = true;
    }
  }

  return (currentDirection);
}

/**
 * If no more move is possible, return true. 
 */
bool checkGameOver() {
  int   i = 0;

  // Check for each frame if a merge is possible (or if the frame is empty...)
  while (i < 16) {
    // If there still have empty frames exit
    if (_grid[i] == 0)
      break;

    if ((i % 4) != 0) { // Check if we can combine with the left frame
      if (_grid[i] == _grid[i - 1])
        break;
    }
    if (((i + 1) % 4) != 0) { // Check if we can combine with the right frame
      if (_grid[i] == _grid[i + 1])
        break;
    }
    if (i > 3) { // Check if we can combine with the upper frame
      if (_grid[i] == _grid[i - 4])
        break;
    }
    if (i < 12) { // Check if we can combine with the bottom frame
      if (_grid[i] == _grid[i + 4])
        break;
    }

    i++;
  }

  // If we ran out of frame without any available merge, game over !
  if (i >= 16)
    return (true);
  return (false);
}

/**
 * Play a melody given in parameters
 */
void playMelody(const int* melody, const int* duration, const int melodySize) {
  int note, noteDuration, pauseBetweenNotes;

  for (note = 0; note < melodySize; note++) {
    noteDuration = 1000 / duration[note];
    pauseBetweenNotes = noteDuration * 1.30;
    tone(PIEZZO_PIN, melody[note], noteDuration);
    delay(pauseBetweenNotes);
    noTone(PIEZZO_PIN);
  }
}

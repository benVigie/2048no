#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "_2048no.h"


void setup() {
  // Initialyze matrix
  _matrix.begin();
  _matrix.setBrightness(20);
  
  // Initialyze grid and random
  memset(_grid, 0, 16);
  randomSeed(analogRead(0));
  
  // Insert 2 number to start the game
  insertNumber();
  insertNumber();
  
  // Debug
  Serial.begin(9600);
  
  // Display the grid
  printGrid();
}

void loop() {
  Direction direction;

  // Get the player direction
  direction = checkMove();
  switch (direction) {
    case Up:
      Serial.println("Go to: Up");
      moveGridTo(0, 1, 4);
      printGrid();
      break;
    case Right:
      Serial.println("Go to: Right");
      moveGridTo(3, 4, -1);
      printGrid();
      break;
    case Down:
      Serial.println("Go to: Down");
      moveGridTo(12, 1, -4);
      printGrid();
      break;
    case Left:
      Serial.println("Go to: Left");
      moveGridTo(0, 4, 1);
      printGrid();
      break;
    default:
      ;
  }
}

/**
*  This function display all grid frame according to their color
*/
void printGrid() {
  uint16_t color;
  int line, col;
  
  _matrix.fillScreen(0);
  
  for (int i = 0; i < 16; i++){
    color = getColor(_grid[i]);
    line = i / 4;
    col = i % 4;
    
    _matrix.drawPixel(col * 2, line * 2, color);
    _matrix.drawPixel(col * 2 + 1, line * 2, color);
    _matrix.drawPixel(col * 2, line * 2 + 1, color);
    _matrix.drawPixel(col * 2 + 1, line * 2 + 1, color);
  }
  
  _matrix.show();
}

/**
*  Return a frame color according to its value
*/
uint16_t getColor(int value) {
  uint16_t color;
  
  switch (value) {
    case 2:
      color = _matrix.Color(255, 0, 0);
      break;
    case 4:
      color = _matrix.Color(0, 255, 0);
      break;
    default:
      color = _matrix.Color(0, 0, 0);
  }
  
  return (color);
}


void moveGridTo(int startPos, int nextRow, int nextFrame) {
  int pos, i, j;
  bool isGridMoved = false;

  debugPrintGrid();

  // While we haven't move each row
  for(i = 0; i < 4; i++) {
      
    pos = startPos;
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

  Serial.println("Move done dude !");
  debugPrintGrid();
}

bool moveFrame(int pos, int nextFrame, int limit) {
  bool hasMoved = false;

  while (pos != limit) {
    
    Serial.print("Try to move frame ");
    Serial.print(pos);
    Serial.print(" to ");
    Serial.println(pos + nextFrame);

    if ((_grid[pos] != 0) && (_grid[pos + nextFrame] == 0)) {
      _grid[pos + nextFrame] = _grid[pos];
      _grid[pos] = 0;
      hasMoved = true;
    }

    pos += nextFrame;
  }
  Serial.println("");

  return (hasMoved);
}


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
 *  Return the joystick position, one of Direction enum
 */
Direction checkMove() {
  int       vertical, horizontal;
  Direction currentDirection      = NoDirection;

  // Move detection
  vertical = map(analogRead(VERT_PIN), 0, 1023, 0, 5);
  horizontal = map(analogRead(HORIZ_PIN), 0, 1023, 0, 5);

  // Check if the joystick is bent to a direction
  if (isDefaultPosition) {
    if ((vertical == 0) || (vertical == 4) || (horizontal == 0) || (horizontal == 4)) {
      isDefaultPosition = false;
      if (vertical == 0)
        currentDirection = Up;
      else if (vertical == 4)
        currentDirection = Down;
      else if (horizontal == 0)
        currentDirection = Right;
      else
        currentDirection = Left;
    }
  }
  // Else check if the joystick is back to its default position
  else if ((!isDefaultPosition) && (vertical == 2) && (horizontal == 2))
    isDefaultPosition = true;

  return (currentDirection);
}

void debugPrintGrid() {
  int i = 0;

  while (i < 16) {
    if (i % 4 == 0)
      Serial.print("[");
    
    Serial.print(_grid[i++]);

    if (i % 4 == 0)
      Serial.println("]");
    else
      Serial.print(", ");
  }
}
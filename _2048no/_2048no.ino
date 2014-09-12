#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


// See https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 6,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Game grid, a 4x4 square
int grid[16];

void setup() {
  // Initialyze matrix
  matrix.begin();
  matrix.setBrightness(20);
  
  // Initialyze grid and random
  memset(grid, 0, 16);
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
  //printGrid();
}

/**
*  This function display all grid frame according to their color
*/
void printGrid() {
  uint16_t color;
  int line, col;
  
  matrix.fillScreen(0);
  
  for (int i = 0; i < 16; i++){
    color = getColor(grid[i]);
    line = i / 4;
    col = i % 4;
    
    matrix.drawPixel(col * 2, line * 2, color);
    matrix.drawPixel(col * 2 + 1, line * 2, color);
    matrix.drawPixel(col * 2, line * 2 + 1, color);
    matrix.drawPixel(col * 2 + 1, line * 2 + 1, color);
  }
  
  matrix.show();
}

/**
*  Return a frame color according to its value
*/
uint16_t getColor(int value) {
  uint16_t color;
  
  switch (value) {
    case 2:
      color = matrix.Color(255, 0, 0);
      break;
    case 4:
      color = matrix.Color(0, 255, 0);
      break;
    default:
      color = matrix.Color(0, 0, 0);
  }
  
  return (color);
}

void insertNumber() {
  long index = random(16);
  
  long number = random(100);
  
  while (grid[index] != 0) {
    index = random(16);
  }
  
  if (number < 66)
    grid[index] = 2;
  else
    grid[index] = 4;
}



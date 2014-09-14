#ifndef __2048NO__
#define __2048NO__

// NeoMatrix control pin
const int MATRIC_PIN  = 6;
// Pin for joystick, test purpose only - To be remove when we will use gyroscop 
const int VERT_PIN    = 5;
const int HORIZ_PIN   = 4;

// Instanciate the Led Matrix
// See https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
Adafruit_NeoMatrix _matrix = Adafruit_NeoMatrix(8, 8, MATRIC_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Game grid, a 4x4 square
int _grid[16];
// Usefull to tag a frame which can't be merge
int _unmergeFrame;

// Boolean use by the joystick
bool  isDefaultPosition = true;


enum Direction {
  NoDirection,
  Up,
  Right,
  Down,
  Left
};

#endif
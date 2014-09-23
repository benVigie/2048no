#ifndef __2048NO__
#define __2048NO__

// NeoMatrix control pin
const int MATRIC_PIN  = 6;
// Pin for joystick, test purpose only - To be remove when we will use gyroscop 
const int VERT_PIN    = 5;
const int HORIZ_PIN   = 4;
// Piezzo buzzer pin
const int PIEZZO_PIN   = 8;

// Instanciate the Led Matrix
// See https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
Adafruit_NeoMatrix _matrix = Adafruit_NeoMatrix(8, 8, MATRIC_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Game grid, a 4x4 square
int _grid[16];
// Use to compute color and give it to the renderer
uint16_t _color[] = { 0, 0, 0, 0 };

// Usefull to tag a frame which can't be merge
int _unmergeFrame;

// Boolean use by the joystick
bool  isDefaultPosition = true;

int _score;


enum Direction {
  NoDirection,
  Up,
  Right,
  Down,
  Left
};

// Music notes
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_G3  196
#define NOTE_G6  1568
#define NOTE_F6  1397
#define NOTE_C1  33

// Game melodies and sounds
const int _startMelody[] = { NOTE_C4, NOTE_D4, NOTE_E4 };
const int _startMelodyDurations[] = { 8, 4, 8 };
const int _startNotes = 3;

const int _combinationMelody[] = { NOTE_G3 };
const int _combinationMelodyDurations[] = { 16 };
const int _combinationNotes = 1;

const int _gameOverMelody[] = { NOTE_G6, NOTE_F6, NOTE_C1 };
const int _gameOverMelodyDurations[] = { 8, 8, 2 };
const int _gameOverNotes = 3;


#endif
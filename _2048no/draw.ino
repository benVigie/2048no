#include "_2048no.h"

/**
*  This function display all grid frame according to their color
*/
void printGrid() {
  int line, col;
  
  _matrix.fillScreen(0);
  
  for (int i = 0; i < 16; i++) {
    getColor(_grid[i]);
    line = i / 4;
    col = i % 4;
    
    // For a 16x16 matrix, we need to set 4 led per frame
    _matrix.drawPixel(col * 2, line * 2, _color[0]);
    _matrix.drawPixel(col * 2 + 1, line * 2, (_color[1] != 0) ? _color[1] : _color[0]);
    _matrix.drawPixel(col * 2, line * 2 + 1, (_color[2] != 0) ? _color[2] : _color[0]);
    _matrix.drawPixel(col * 2 + 1, line * 2 + 1, (_color[3] != 0) ? _color[3] : _color[0]);
  }
  
  _matrix.show();
}

/**
*  Return a frame color according to its value
*/
void getColor(int value) {
  // Reset previous color
  memset(_color, 0, sizeof(*_color) * 4);
  
  switch (value) {
    case 2:
      _color[0] = _matrix.Color(237, 255, 209);
      break;
    case 4:
      _color[0] = _matrix.Color(255, 250, 114);
      break;
    case 8:
      _color[0] = _matrix.Color(255, 160, 0);
      break;
    case 16:
      _color[0] = _matrix.Color(255, 47, 0);
      break;
    case 32:
      _color[0] = _matrix.Color(255, 0, 96);
      break;
    case 64:
      _color[0] = _matrix.Color(206, 3, 255);
      break;
    case 128:
      _color[0] = _matrix.Color(0, 136, 255);
      break;
    case 256:
      _color[0] = _matrix.Color(0, 246, 255);
      break;
    case 512:
      _color[0] = _matrix.Color(0, 255, 20);
      break;
    case 1024:
      _color[0] = _matrix.Color(0, 255, 115);
      break;
    case 2048:
      _color[0] = _matrix.Color(255, 160, 0);
      _color[1] = _matrix.Color(255, 0, 96);
      _color[2] = _matrix.Color(206, 3, 255);
      _color[3] = _matrix.Color(255, 47, 0);
      break;
    case 4096:
      _color[0] = _matrix.Color(0, 136, 255);
      _color[1] = _matrix.Color(0, 255, 20);
      _color[2] = _matrix.Color(0, 255, 115);
      _color[3] = _matrix.Color(0, 246, 255);
      break;
    default:
      _color[0] = _matrix.Color(0, 0, 0);
  }
}
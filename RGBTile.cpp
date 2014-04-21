/***********
*  Arduino Library for the 5 x 5 RGB LED "tile" made by Burgeon Group
*
* Natalie Freed, June 2013
*
* Uses Adafruit_WS2801 library from adafruit.com to interface with LED strips,
* adds wrapper functions for more easily playing with pixels,
* and some effect functions (drawing letters, twinkling effects...)
*
***********/

#include "Arduino.h"
#include "RGBTile.h"
// #include "SPI.h"

RGBTile::RGBTile()
{
  uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
  uint8_t clockPin = 3;    // Green wire on Adafruit Pixels

  // Set the first variable to the number of pixels in a row and
  // the second value to number of pixels in a column.
  _strip = Adafruit_WS2801((uint16_t)NUM_ROWS, (uint16_t)NUM_COLS, dataPin, clockPin);
  _strip.begin();
  
  for(int i=0;i<NUM_ROWS;i++)
  {
    for(int j=0;j<NUM_COLS;j++)
    {
      _colors[i][j] = Color(255,255,255); //default color is white
    }
  }
}

// Create a 24 bit color value from R,G,B
// From Adafruit_WS2801 library (examples)
uint32_t RGBTile::Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

void RGBTile::drawLetter(char c)
{
  load_bitmap(c);
  for(int i=0;i<NUM_ROWS;i++)
  {
    for(int j=0;j<NUM_COLS;j++)
    {
      int k = map(i, 0, NUM_ROWS-1, NUM_ROWS-1, 0);
      int m = map(j, 0, NUM_COLS-1, NUM_COLS-1, 0);
      _strip.setPixelColor(m, k, ((0x1 << j) & bitmap[i])? _colors[m][k]:Color(0,0,0));
    }  
  }
  _strip.show();
}

void RGBTile::twinkle() {
  int n = random(0, 5);
  for(int i=0;i<_strip.numPixels();i++)
  {
    _strip.setPixelColor(i, Color(0,0,0));
  }
  for(int k=0;k<n;k++)
  {
    int r = random(0, _strip.numPixels()*2);
    for(int i=0;i<_strip.numPixels();i++)
    {
      if(i == r)
      {
        _strip.setPixelColor(i, _colors[i/NUM_COLS][i%NUM_COLS]);
  //      strip.setPixelColor(i, Color(0,0,0));
      }
    }
  }
  _strip.show();
}

void RGBTile::drawAll()
{
   for(int i=0;i<NUM_ROWS;i++)
   {
    for(int j=0;j<NUM_COLS;j++)
    {
      _strip.setPixelColor(i, j, _colors[i][j]);
    }  
  }
   _strip.show(); 
}

void RGBTile::drawPixel(int x, int y)
{
  _strip.setPixelColor(x, y, _colors[x][y]); 
  _strip.show();
}

void RGBTile::colorPixel(int x, int y, byte r, byte g, byte b)
{
  _colors[x][y] = Color(r, g, b); 
}

void RGBTile::colorPixel(int x, int y, uint32_t c)
{
  _colors[x][y] = c;
}

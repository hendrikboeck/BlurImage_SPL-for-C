/*
 * File: Color.h
 * -------------
 * Author: Hendrik Böck
 * 
 */

#ifndef COLOR_H_
#define COLOR_H_

struct ColorCDT {
    int red;
    int green;
    int blue;
};

typedef struct ColorCDT *Color;

Color newColor(int red, int green, int blue);
Color newColorFromPixel(int pixel);
void deleteColor(Color color);
Color mergeColors(Color *colors, int colorsLength);

#endif
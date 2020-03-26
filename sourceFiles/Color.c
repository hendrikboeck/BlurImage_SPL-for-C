/*
 * File: Color.c
 * -------------
 * Author: Hendrik Böck
 * 
 */

#include "Color.h"

#include "cslib.h"
#include "gobjects.h"

Color newColor(int red, int green, int blue) {
    Color color = newBlock(Color);

    color->red = red;
    color->green = green;
    color->blue = blue;
    return color;
}

Color newColorFromPixel(int pixel) {
    Color color = newBlock(Color);

    color->red = getRed(pixel);
    color->green = getGreen(pixel);
    color->blue = getBlue(pixel);
    return color;
}

void deleteColor(Color color) { freeBlock(color); }

Color mergeColors(Color *colors, int colorsLength) {
    long red = 0, green = 0, blue = 0;

    int colorCount = 0;
    for (int i = 0; i < colorsLength; i++) {
        if (colors[i] != NULL) {
            red += colors[i]->red;
            green += colors[i]->green;
            blue += colors[i]->blue;
            colorCount++;
        }
    }
    if (colorCount != 0) {
        red /= colorCount;
        green /= colorCount;
        blue /= colorCount;
    }

    return newColor((int)red, (int)green, (int)blue);
}

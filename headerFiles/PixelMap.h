/*
 * File: ArrayList.h
 * -----------------
 * Author: Hendrik Böck
 *
 */

#ifndef PIXELMAP_H_
#define PIXELMAP_H_

#include "Vector2D.h"
#include "cslib.h"

struct _PixelMap {
    Vector2D *arr;
    size_t length;
    size_t capacity;
};

typedef struct _PixelMap *PixelMap;

PixelMap newPixelMap();
void deletePixelMap(PixelMap map);
PixelMap appendPixelMap(PixelMap map, Vector2D pixelVector);

#endif
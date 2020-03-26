/*
 * File: Vector2D.c
 * ----------------
 * Author: Hendrik Böck
 * 
 */

#include "Vector2D.h"

#include "cslib.h"

Vector2D newVector2D(int x, int y) {
    Vector2D vec = newBlock(Vector2D);

    vec->x = x;
    vec->y = y;
    return vec;
}

void deleteVector2D(Vector2D vec) { freeBlock(vec); }

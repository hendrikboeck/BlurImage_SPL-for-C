/*
 * File: Vector2D.h
 * ----------------
 * Author: Hendrik Böck
 * 
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

struct Vector2DCDT {
    int x;
    int y;
};

typedef struct Vector2DCDT *Vector2D;

Vector2D newVector2D(int x, int y);
void deleteVector2D(Vector2D vec);

#endif
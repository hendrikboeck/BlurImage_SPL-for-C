#include "PixelMap.h"

#include <string.h>

#include "cslib.h"

PixelMap newPixelMap() {
    PixelMap map = newBlock(PixelMap);

    map->arr = newArray(2, Vector2D);
    map->capacity = 2;
    map->length = 0;
    return map;
}

void deletePixelMap(PixelMap map) {
    for (int i = 0; i < map->length; i++) freeBlock(map->arr[i]);
    freeBlock(map->arr);
    freeBlock(map);
}

PixelMap appendPixelMap(PixelMap map, Vector2D pixelVector) {
    if (map->length == map->capacity) {
        Vector2D *newArr = newArray(2 * map->capacity, Vector2D);
        memcpy(newArr, map->arr, map->capacity * sizeof(Vector2D));
        map->capacity *= 2;
        freeBlock(map->arr);
        map->arr = newArr;
    }
    map->arr[map->length] = pixelVector;
    map->length++;

    return map;
}
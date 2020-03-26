#include "Color.h"
#include "PixelMap.h"
#include "Vector2D.h"
#include "cslib.h"
#include "gobjects.h"
#include "gwindow.h"

/*
 * CONSTANTS
 */
#define WINDOW_WIDTH 396
#define WINDOW_HEIGHT 249

/*
 * GLOBAL VARIABLES
 */
GWindow view;

/*
 * PRE-DECLARATION OF FUNCTIONS
 */
void blurImage(GImage img, int blurRadius);
int blurRGBPixel(int **pixels, PixelMap blurMap);
int blurRGBAPixel(int **pixels, PixelMap blurMap);
PixelMap getPixelMap(bool **bresenhamCircle, int radius, int x, int y,
                     int picWidth, int picHeight);
void addCirclePoint(int x, int y, bool **arr, int length);
bool **getBresenhamCircle(int radius);

/*
 * MAIN-FUNCTION (call of program)
 */
int main(int argc, char **argv) {
    view = newGWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    GImage img = newGImage("../../images/Obama.png");
    addAt(view, img, 0, 0);
    GImage obama = newGImage("../../images/Obama.png");
    blurImage(obama, 4);
    addAt(view, obama, getWidthGObject(img), 0);

    return 0;
}

/*
 * IMPLEMENTATION OF PRE-DECLARED FUNCTIONS
 */
void blurImage(GImage img, int blurRadius) {
    int width = getWidthGObject(img);
    int height = getHeightGObject(img);
    int **sourcePixels = getPixelArray(img);
    int **targetPixels = newArray(height, int *);
    for (int i = 0; i < height; i++) targetPixels[i] = newArray(width, int);
    bool **bresenhamCircle = getBresenhamCircle(blurRadius);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            PixelMap blurMap =
                getPixelMap(bresenhamCircle, blurRadius, x, y, width, height);
            targetPixels[y][x] = blurRGBAPixel(sourcePixels, blurMap);
            deletePixelMap(blurMap);
        }
    }

    setPixelArray(img, targetPixels);

    for (int i = 0; i < height; i++) freeBlock(sourcePixels[i]);
    freeBlock(sourcePixels);
    for (int i = 0; i < height; i++) freeBlock(targetPixels[i]);
    freeBlock(targetPixels);
    for (int i = 0; i < (2 * blurRadius) + 1; i++)
        freeBlock(bresenhamCircle[i]);
    freeBlock(bresenhamCircle);
}

int blurRGBPixel(int **pixels, PixelMap blurMap) {
    Color *colors = newArray(blurMap->length, Color);

    for (int i = 0; i < blurMap->length; i++)
        colors[i] =
            newColorFromPixel(pixels[(blurMap->arr[i]->y)][blurMap->arr[i]->x]);

    Color result = mergeColors(colors, blurMap->length);
    freeBlock(colors);

    return createRGBPixel(result->red, result->green, result->blue);
}

int blurRGBAPixel(int **pixels, PixelMap blurMap) {
    int rgbPixel = blurRGBPixel(pixels, blurMap);
    long alpha = 0;

    for (int i = 0; i < blurMap->length; i++)
        alpha += getAlpha(pixels[(blurMap->arr[i]->y)][blurMap->arr[i]->x]);

    alpha /= blurMap->length;

    return createRGBAPixel(getRed(rgbPixel), getGreen(rgbPixel),
                           getBlue(rgbPixel), (int)alpha);
}

PixelMap getPixelMap(bool **bresenhamCircle, int radius, int x, int y,
                     int picWidth, int picHeight) {
    int length = (2 * radius) + 1;

    // extract the coordinates
    PixelMap blurMap = newPixelMap();
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (bresenhamCircle[i][j]) {
                int xP = x + (i - radius);
                int yP = y + (j - radius);
                if (xP >= 0 && xP < picWidth && yP >= 0 && yP < picHeight) {
                    Vector2D vec = newVector2D(xP, yP);
                    appendPixelMap(blurMap, vec);
                }
            }
        }
    }

    return blurMap;
}

void addCirclePoint(int x, int y, bool **arr, int length) {
    if (x < length && x >= 0 && y < length && y >= 0) arr[x][y] = true;
}

bool **getBresenhamCircle(int radius) {
    float x1 = radius, y1 = radius, r = radius;
    float x = 0, y = r, p = 3 - (2 * r);

    // initialize a circle-array
    int length = (2 * radius) + 1;
    bool **circle = newArray(length, bool *);
    for (int i = 0; i < length; i++) circle[i] = newArray(length, bool);
    for (int i = 0; i < length; i++)
        for (int j = 0; j < length; j++) circle[i][j] = false;

    // create a circle after the Bresenham’s circle drawing algorithm
    while (x <= y) {
        addCirclePoint((int)(x1 + x), (int)(y1 + y), circle, length);
        addCirclePoint((int)(x1 - x), (int)(y1 + y), circle, length);
        addCirclePoint((int)(x1 + x), (int)(y1 - y), circle, length);
        addCirclePoint((int)(x1 - x), (int)(y1 - y), circle, length);
        addCirclePoint((int)(x1 + y), (int)(y1 + x), circle, length);
        addCirclePoint((int)(x1 - y), (int)(y1 + x), circle, length);
        addCirclePoint((int)(x1 + y), (int)(y1 - x), circle, length);
        addCirclePoint((int)(x1 - y), (int)(y1 - x), circle, length);
        x++;
        if (p < 0) {
            p = p + 4 * x + 6;
        } else {
            p = p + 4 * (x - y) + 10;
            y--;
        }
    }

    // fill the circle-array
    for (int i = 0; i < length; i++) {
        bool fill = false;
        for (int j = 0; j < length; j++) {
            if (circle[i][j] == true && fill == false && j < (length / 2))
                fill = true;
            else if (circle[i][j] == true && fill == true && j > (length / 2))
                fill = false;
            if (fill) circle[i][j] = true;
        }
    }

    return circle;
}

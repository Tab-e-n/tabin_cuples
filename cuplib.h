#ifndef CUPLIB
#define CUPLIB

#include <raylib.h>

#define SCREEN_SIZE (Vector2){640, 480}
#define SCREEN_SIZE_HALF (Vector2){320, 240}
#define FRAME 0.016

#define TRANS_PURPLE (Color){200, 122, 255, 128}
#define TRANS_RED (Color){230, 41, 55, 128}
#define TRANS_BLUE (Color){0, 121, 241, 128}
#define TRANS_GREEN (Color){0, 241, 121, 128}

float absf(float x);
float maxf(float x, float y);
float minf(float x, float y);

#endif

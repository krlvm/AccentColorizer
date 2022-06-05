#pragma once
#include "framework.h"

typedef void (*BitmapHandler)(int* r, int* g, int* b, int* a);
bool RecolorizeBitmap(HBITMAP hbm, BitmapHandler handler);
#pragma once
#include "framework.h"

DWORD rgb2bgr(COLORREF rgb);

struct rgb_t
{
	double r, g, b;
};

struct hsv_t
{
	double h, s, v;
};

hsv_t rgb2hsv(rgb_t in);
rgb_t hsv2rgb(hsv_t in);
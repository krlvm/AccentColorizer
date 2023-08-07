#include "BitmapHelper.h"

bool IterateBitmap(HBITMAP hbm, BitmapPixelHandler handler)
{
    BITMAP bm;
    GetObject(hbm, sizeof(bm), &bm);

    if (!hbm || bm.bmBitsPixel != 32)
    {
        return false;
    }

    BYTE* pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
    GetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    BYTE* pPixel;
    int x, y;
    int r, g, b, a;

    for (y = 0; y < bm.bmHeight; y++)
    {
        pPixel = pBits + bm.bmWidth * 4 * y;

        for (x = 0; x < bm.bmWidth; x++)
        {
            r = pPixel[2] & 0xFFFFFF;
            g = pPixel[1] & 0xFFFFFF;
            b = pPixel[0] & 0xFFFFFF;
            a = pPixel[3] & 0xFFFFFF;

            handler(r, g, b, a);

            pPixel[2] = r;
            pPixel[1] = g;
            pPixel[0] = b;
            pPixel[3] = a;

            pPixel += 4;
        }
    }

    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    delete[] pBits;
    return true;
}
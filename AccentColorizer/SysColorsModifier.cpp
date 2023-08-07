#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

constexpr int aSysElements[] = {
	COLOR_ACTIVECAPTION,
	COLOR_GRADIENTACTIVECAPTION,
	COLOR_HIGHLIGHT,
	COLOR_HOTLIGHT,
	COLOR_MENUHILIGHT
};
constexpr size_t nSysElements = sizeof(aSysElements) / sizeof(*aSysElements);

void ModifySysColors()
{
	DWORD aNewColors[nSysElements];

	COLORREF dwCurrentColor;
	rgb_t rgbVal;
	hsv_t hsvVal;

	for (int i = 0; i < nSysElements; i++)
	{
		dwCurrentColor = GetSysColor(aSysElements[i]);

		rgbVal = {
			(double)GetRValue(dwCurrentColor),
			(double)GetGValue(dwCurrentColor),
			(double)GetBValue(dwCurrentColor)
		};
		hsvVal = rgb2hsv(rgbVal);

		hsvVal.h = g_hsvAccentH;

		rgbVal = hsv2rgb(hsvVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
	}

	SetSysColors(nSysElements, aSysElements, aNewColors);
}
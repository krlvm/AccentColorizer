#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

const int aSysElements[] = {
	COLOR_ACTIVECAPTION,
	COLOR_GRADIENTACTIVECAPTION,
	COLOR_HIGHLIGHT,
	COLOR_HOTLIGHT,
	COLOR_MENUHILIGHT
};
const size_t nSysElements = sizeof(aSysElements) / sizeof(*aSysElements);

void ModifySysColors(COLORREF dwAccentColor) {
	int hsvAccentH = GetHSVh(dwAccentColor);

	DWORD aNewColors[nSysElements];

	for (int i = 0; i < nSysElements; i++)
	{
		COLORREF dwCurrentColor = GetSysColor(aSysElements[i]);

		rgb rgbVal = rgb{
			(double)GetRValue(dwCurrentColor),
			(double)GetGValue(dwCurrentColor),
			(double)GetBValue(dwCurrentColor)
		};
		hsv hsvVal = rgb2hsv(rgbVal);

		hsvVal.h = hsvAccentH;

		rgbVal = hsv2rgb(hsvVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
	}

	SetSysColors(nSysElements, aSysElements, aNewColors);
}
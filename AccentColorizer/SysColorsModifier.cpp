#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

#define SYS_COLORS_SIZE 5

void ModifySysColors(COLORREF dwAccentColor) {
	int hsvAccentH = GetHSVh(dwAccentColor);

	int aElements[SYS_COLORS_SIZE] =
	{
		COLOR_ACTIVECAPTION,
		COLOR_GRADIENTACTIVECAPTION,
		COLOR_HIGHLIGHT,
		COLOR_HOTLIGHT,
		COLOR_MENUHILIGHT
	};
	DWORD aNewColors[SYS_COLORS_SIZE];

	for (int i = 0; i < SYS_COLORS_SIZE; i++)
	{
		COLORREF dwCurrentColor = GetSysColor(aElements[i]);

		rgb rgbVal = rgb{ (double)GetRValue(dwCurrentColor), (double)GetGValue(dwCurrentColor), (double)GetBValue(dwCurrentColor) };
		hsv hsvVal = rgb2hsv(rgbVal);

		hsvVal.h = hsvAccentH;

		rgbVal = hsv2rgb(hsvVal);

		aNewColors[i] = RGB(rgbVal.r, rgbVal.g, rgbVal.b);
	}

	SetSysColors(SYS_COLORS_SIZE, aElements, aNewColors);
}
#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

const int size = 5;

void ModifySysColors(COLORREF accentColor) {
	int aElements[size] =
	{
		COLOR_ACTIVECAPTION,
		COLOR_GRADIENTACTIVECAPTION,
		COLOR_HIGHLIGHT,
		COLOR_HOTLIGHT,
		COLOR_MENUHILIGHT
	};
	DWORD aNewColors[size];

	for (int i = 0; i < size; i++)
	{
		aNewColors[i] = accentColor;
	}

	SetSysColors(size, aElements, aNewColors);
}
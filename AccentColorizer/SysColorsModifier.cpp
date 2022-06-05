#include "SysColorsModifier.h"
#include "AccentColorHelper.h"

const int size = 5;

void ModifySysColors() {
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
		aNewColors[i] = RGB(GetRValue(accent), GetGValue(accent), GetBValue(accent));
	}

	SetSysColors(size, aElements, aNewColors);
}
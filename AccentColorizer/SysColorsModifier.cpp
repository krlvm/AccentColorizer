#include "SysColorsModifier.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

const int size = 5;

void ModifySysColors() {
	if (!accentOpaqueAvailable)
	{
		return;
	}

	int aElements[size] =
	{
		COLOR_ACTIVECAPTION,
		COLOR_GRADIENTACTIVECAPTION,
		COLOR_HIGHLIGHT,
		COLOR_HOTLIGHT,
		COLOR_MENUHILIGHT
	};
	DWORD aNewColors[size];

	COLORREF color = RGB(GetRValue(accentOpaque), GetGValue(accentOpaque), GetBValue(accentOpaque));
	for (int i = 0; i < size; i++)
	{
		aNewColors[i] = color;
	}

	SetSysColors(size, aElements, aNewColors);
}
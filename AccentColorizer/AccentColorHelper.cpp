#include "AccentColorHelper.h"
#include "ColorHelper.h"

COLORREF g_dwAccent;

bool UpdateAccentColors()
{
	COLORREF dwAccentRGB;
	BOOL bIsColorOpaque;

	DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);

	DWORD dwAccent = RGB2BGR(dwAccentRGB);

	if (g_dwAccent == dwAccent)
	{
		return false;
	}

	g_dwAccent = dwAccent;
	return true;
}

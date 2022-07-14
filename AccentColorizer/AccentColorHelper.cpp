#include "AccentColorHelper.h"
#include <dwmapi.h>
#include "ColorHelper.h"

COLORREF accent;

bool UpdateAccentColors()
{
	COLORREF dwAccentRGB;
	BOOL bIsColorOpaque;

	DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);

	DWORD dwAccent = RGB2BGR(dwAccentRGB);

	if (accent == dwAccent)
	{
		return false;
	}

	accent = dwAccent;
	return true;
}

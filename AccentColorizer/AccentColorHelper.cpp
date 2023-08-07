#include "AccentColorHelper.h"
#include "ColorHelper.h"

COLORREF g_dwAccent;
int g_hsvAccentH;

bool UpdateAccentColor()
{
	COLORREF dwAccentRGB;
	BOOL bIsColorOpaque;

	DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);

	DWORD dwAccent = rgb2bgr(dwAccentRGB);

	if (g_dwAccent == dwAccent)
	{
		return false;
	}

	g_dwAccent = dwAccent;
	g_hsvAccentH = rgb2hsv({
		(double) GetRValue(dwAccent) / 255,
		(double) GetGValue(dwAccent) / 255,
		(double) GetBValue(dwAccent) / 255 }).h;

	return true;
}

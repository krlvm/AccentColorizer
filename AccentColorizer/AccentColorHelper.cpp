#include "AccentColorHelper.h"
#include <dwmapi.h>
#include "ColorHelper.h"

COLORREF accent;

void UpdateAccentColors()
{
	COLORREF dwAccentRGB;
	BOOL bIsColorOpaque;

	DwmGetColorizationColor(&dwAccentRGB, &bIsColorOpaque);

	accent = RGB2BGR(dwAccentRGB);
}

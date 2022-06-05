#include "AccentColorHelper.h"
#include <dwmapi.h>
#include <VersionHelpers.h>
#include "ColorHelper.h"

#define RGB2BGR(a_ulColor) (a_ulColor & 0xFF000000) | ((a_ulColor & 0xFF0000) >> 16) | (a_ulColor & 0x00FF00) | ((a_ulColor & 0x0000FF) << 16)

struct DWMCOLORIZATIONPARAMS {
	DWORD dwColor;
	DWORD dwAfterglow;
	DWORD dwColorBalance;
	DWORD dwAfterglowBalance;
	DWORD dwBlurBalance;
	DWORD dwGlassReflectionIntensity;
	DWORD dwOpaqueBlend;
};
static HRESULT(WINAPI* DwmGetColorizationParameters)(DWMCOLORIZATIONPARAMS* color);
bool InitializeDwmApi()
{
	HMODULE hDwmApi = LoadLibrary(L"dwmapi.dll");
	if (!hDwmApi)
	{
		return FALSE;
	}
	DwmGetColorizationParameters = reinterpret_cast<decltype(DwmGetColorizationParameters)>(GetProcAddress(hDwmApi, (LPCSTR)127));
	return TRUE;
}

#include <io.h>
#include <fcntl.h>

COLORREF accent;
COLORREF accentOpaque;
bool accentOpaqueAvailable;

COLORREF _accentRgb;
BOOL _accentOpaque;

DWORD SetOpacity(DWORD color, float opacity) {
	int alpha = (color >> 24) & 0xff;
	int r = (color >> 16) & 0xff;
	int g = (color >> 8) & 0xff;
	int b = color & 0xff;

	int newAlpha = ceil(alpha * opacity);

	UINT newColor = r << 16;
	newColor += g << 8;
	newColor += b;
	newColor += (newAlpha << 24);

	return (DWORD)newColor;
}

void UpdateAccentColors()
{
	DwmGetColorizationColor(&_accentRgb, &_accentOpaque);

	accent = RGB2BGR(_accentRgb);
	if (_accentOpaque)
	{
		accentOpaque = accent;
		accentOpaqueAvailable = true;
	}
	else
	{
		// Should run only on Windows Vista/7
		// because on Windows 8+ bOpaque is always true

		accentOpaqueAvailable = false;

		if (InitializeDwmApi())
		{
			DWMCOLORIZATIONPARAMS dwmColor;
			if (SUCCEEDED(DwmGetColorizationParameters(&dwmColor)))
			{
				DWORD color = dwmColor.dwColor;
				color = (color & 0x00ffffff) | (255 << 24);

				accentOpaque = RGB2BGR(RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
				accentOpaqueAvailable = true;
			}
		}
	}
}
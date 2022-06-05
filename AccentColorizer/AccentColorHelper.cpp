#include "AccentColorHelper.h"

// https://social.msdn.microsoft.com/Forums/en-US/16b70775-d87e-42d3-aa8f-41d7d6888c66/how-to-get-colors-of-default-app-mode-quotdarkquot-in-my-win32-app?forum=windowsgeneraldevelopmentissues

typedef DWORD(WINAPI* PGetImmersiveColorFromColorSetEx)(UINT dwImmersiveColorSet, UINT dwImmersiveColorType, bool bIgnoreHighContrast, UINT dwHighContrastCacheMode);
typedef WCHAR** (WINAPI* PGetImmersiveColorNamedTypeByIndex)(UINT dwImmersiveColorType);
typedef int (WINAPI* PGetImmersiveColorTypeFromName)(const WCHAR* name);
typedef int (WINAPI* PGetImmersiveUserColorSetPreference)(bool bForceCheckRegistry, bool bSkipCheckOnFail);

PGetImmersiveColorFromColorSetEx pGetImmersiveColorFromColorSetEx = NULL;
PGetImmersiveColorTypeFromName pGetImmersiveColorTypeFromName = NULL;
PGetImmersiveUserColorSetPreference pGetImmersiveUserColorSetPreference = NULL;

COLORREF accent;

COLORREF accentLight1;
COLORREF accentLight2;
COLORREF accentLight3;

COLORREF accentDark1;
COLORREF accentDark2;
COLORREF accentDark3;

DWORD GetImmersiveColorRGB(const WCHAR* name)
{
	return pGetImmersiveColorFromColorSetEx(pGetImmersiveUserColorSetPreference(false, false), pGetImmersiveColorTypeFromName(name), false, 0);
}

void UpdateAccentColors()
{
	HMODULE hUxTheme = LoadLibrary(TEXT("uxtheme.dll"));
	if (hUxTheme)
	{
		pGetImmersiveColorFromColorSetEx = (PGetImmersiveColorFromColorSetEx)GetProcAddress(hUxTheme, MAKEINTRESOURCEA(95));
		pGetImmersiveColorTypeFromName = (PGetImmersiveColorTypeFromName)GetProcAddress(hUxTheme, MAKEINTRESOURCEA(96));
		pGetImmersiveUserColorSetPreference = (PGetImmersiveUserColorSetPreference)GetProcAddress(hUxTheme, MAKEINTRESOURCEA(98));

		accent = GetImmersiveColorRGB(L"ImmersiveSystemAccent");
		accentLight1 = GetImmersiveColorRGB(L"ImmersiveSystemAccentLight1");
		accentLight2 = GetImmersiveColorRGB(L"ImmersiveSystemAccentLight2");
		accentLight3 = GetImmersiveColorRGB(L"ImmersiveSystemAccentLight3");

		accentDark1 = GetImmersiveColorRGB(L"ImmersiveSystemAccentDark1");
		accentDark2 = GetImmersiveColorRGB(L"ImmersiveSystemAccentDark2");
		accentDark3 = GetImmersiveColorRGB(L"ImmersiveSystemAccentDark3");
	}
}
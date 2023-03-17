#include "SystemHelper.h"
#include <VersionHelpers.h>

WINDOWSVERSION g_winver;

void DetectWindowsVersion()
{
	if (IsWindows10OrGreater())
	{
		g_winver = WIN_10;
	}
	else if (IsWindows8OrGreater())
	{
		g_winver = WIN_8;
	}
	else if (IsWindows7OrGreater())
	{
		g_winver = WIN_7;
	}
	else
	{
		g_winver = WIN_VISTA;
	}
}
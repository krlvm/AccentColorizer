#include "SystemHelper.h"
#include <VersionHelpers.h>

int winver;

void DetectWindowsVersion()
{
	if (IsWindows10OrGreater())
	{
		winver = 10;
	}
	else if (IsWindows8OrGreater())
	{
		winver = 8;
	}
	else if (IsWindows7OrGreater())
	{
		winver = 7;
	}
	else
	{
		winver = 6;
	}
}
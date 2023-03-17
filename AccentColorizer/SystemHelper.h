#pragma once
#include "framework.h"

enum WINDOWSVERSION
{
	WIN_VISTA,
	WIN_7,
	WIN_8,
	WIN_10
};

extern WINDOWSVERSION g_winver;

void DetectWindowsVersion();
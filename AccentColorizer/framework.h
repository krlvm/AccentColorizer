#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <shellapi.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <dwmapi.h>
#include <wtsapi32.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "wtsapi32.lib")
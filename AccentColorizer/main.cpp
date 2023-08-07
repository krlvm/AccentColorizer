#include "AccentColorHelper.h"
#include "SysColorsModifier.h"
#include "StyleModifier.h"
#include "SettingsHelper.h"
#include "SystemHelper.h"

constexpr LPCWSTR szWindowClass = L"ACCENTCOLORIZER";
HANDLE hMutex;

void ApplyAccentColorization()
{
	if (!UpdateAccentColor())
	{
		// Accent Colors have not been changed.
		// There's a bug in Windows 10 1809+ because of which
		// WM_DWMCOLORIZATIONCOLORCHANGED message is sent multiple times,
		// it also affects accent color changing performance in general.
		// Apparently it is fixed in Windows 11 version 22H2
		return;
	}
	ModifySysColors();
	ModifyStyles();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DWMCOLORIZATIONCOLORCHANGED ||
		message == WM_DPICHANGED ||
		message == WM_THEMECHANGED ||
		(message == WM_WTSSESSION_CHANGE && wParam == WTS_SESSION_UNLOCK)
	)
	{
		if (message != WM_DWMCOLORIZATIONCOLORCHANGED)
		{
			// We need to re-apply colorization completely because:
			//  a) DPI changed
			//  b) Visual Theme has been changed, and bitmaps were reset
			//  c) Another user was probably logged in, and we need to override the colors and bitmaps
			//  d) Device was turned on after sleep, and colors and bitmaps probably were reset
			g_dwAccent = NULL;
		}
		ApplyAccentColorization();
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
	hMutex = CreateMutex(NULL, TRUE, szWindowClass);
	if (!hMutex || ERROR_ALREADY_EXISTS == GetLastError())
	{
		return 1;
	}

	DetectWindowsVersion();

	g_bColorizeMenus = IsMenuColorizationEnabled();
	g_bColorizeProgressBar = IsProgressBarColorizationEnabled();

	ApplyAccentColorization();
	if (g_winver < WIN_8)
	{
		g_dwAccent = NULL;
	}

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szWindowClass;
	if (!RegisterClassEx(&wcex))
	{
		return 2;
	}

	HWND hWnd = CreateWindowEx(0, szWindowClass, nullptr, 0, 0, 0, 0, 0, nullptr, NULL, NULL, NULL);
	WTSRegisterSessionNotification(hWnd, NOTIFY_FOR_THIS_SESSION);

	if (g_winver < WIN_8)
	{
		SendMessageTimeout(hWnd, WM_DWMCOLORIZATIONCOLORCHANGED, g_dwAccent, g_dwAccent, SMTO_NORMAL, 2000, nullptr);
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return (int)msg.wParam;
}
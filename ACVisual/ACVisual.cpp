// ACVisual.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ACVisual.h"
#include <Uxtheme.h>

#pragma comment(lib, "uxtheme.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

#define BTN_E 5
HWND button;

HWND clzName;
HWND ipart;
HWND istate;
HWND iprop;

char cclz[80], cpart[20], cstate[20], cprop[20];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ACVISUAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ACVISUAL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ACVISUAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ACVISUAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HWND rndr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        button = CreateWindow("button", "Load", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            30, 30, 300, 30, hWnd, (HMENU) BTN_E, GetModuleHandle(NULL), NULL);

        clzName = CreateWindow("edit", "clz", WS_VISIBLE | WS_CHILD | WS_BORDER,
            30, 60, 150, 50, hWnd, NULL, GetModuleHandle(NULL), NULL);
        ipart = CreateWindow("edit", "ipart", WS_VISIBLE | WS_CHILD | WS_BORDER,
            30, 90, 150, 50, hWnd, NULL, GetModuleHandle(NULL), NULL);
        istate = CreateWindow("edit", "istate", WS_VISIBLE | WS_CHILD | WS_BORDER,
            30, 120, 150, 50, hWnd, NULL, GetModuleHandle(NULL), NULL);
        iprop = CreateWindow("edit", "iprop", WS_VISIBLE | WS_CHILD | WS_BORDER,
            30, 150, 150, 50, hWnd, NULL, GetModuleHandle(NULL), NULL);

        rndr = CreateWindowEx(0,
            "Static",
            "",
            WS_CHILD | WS_VISIBLE | SS_BITMAP,
            0,
            0,
            500,
            500,
            hWnd,
            NULL,
            hInst,
            NULL);

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BTN_E:
            {
                GetWindowText(clzName, &cclz[0], 80);
                GetWindowText(ipart, &cpart[0], 20);
                GetWindowText(istate, &cstate[0], 20);
                GetWindowText(iprop, &cprop[0], 20);

                ::MessageBox(hWnd, cclz, cstate, MB_OK);

                HBITMAP hBitmap;

                wchar_t wtext[80];
                mbstowcs(wtext, cclz, strlen(cclz) + 1);//Plus null
                LPWSTR ptr = wtext;

                HTHEME hTheme = OpenThemeData(GetForegroundWindow(), ptr);
                GetThemeBitmap(hTheme, atoi(cpart), atoi(cstate), atoi(cprop), GBF_DIRECT, &hBitmap);
                CloseThemeData(hTheme);

                SendMessage(rndr, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

                break;
            }
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

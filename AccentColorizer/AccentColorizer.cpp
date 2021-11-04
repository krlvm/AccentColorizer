#include <iostream>
#include <Windows.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")

#include "AccentColorHelper.h"

/*
const COLORREF accent = RGB(136, 23, 152);
const COLORREF accentLight1 = RGB(203, 61, 187);
const COLORREF accentLight2 = RGB(242, 102, 227);
const COLORREF accentLight3 = RGB(247, 184, 255);
*/


#pragma region Pixel Color

inline int PixClr(int val)
{
    return val & 0xFFFFFF;
}

inline int PixR(BYTE* pPixel)
{
    return PixClr(pPixel[2]);
}
inline int PixG(BYTE* pPixel)
{
    return PixClr(pPixel[1]);
}
inline int PixB(BYTE* pPixel)
{
    return PixClr(pPixel[0]);
}
inline int PixA(BYTE* pPixel)
{
    return PixClr(pPixel[3]);
}

#pragma endregion

#define TEST 0

int RecolorizeBitmap(HBITMAP hbm)
{
    BITMAP bm;
    GetObject(hbm, sizeof(bm), &bm);

    if (!hbm || bm.bmBitsPixel != 32) {
        return FALSE;
    }

    BYTE* pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
    GetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    for (int y = 0; y < bm.bmHeight; y++) {
        BYTE* pPixel = (BYTE*)pBits + bm.bmWidth * 4 * y;

        for (int x = 0; x < bm.bmWidth; x++) {

            int r = PixR(pPixel); // [2]
            int g = PixG(pPixel); // [1]
            int b = PixB(pPixel); // [0]
            int a = PixA(pPixel); // [3]

            if (TEST && ((r || g || b)))
            {
                std::cout << "rgba(" << r << ", " << g << ", " << b << ", " << (double)a / 255 << ")" << std::endl;
                continue;
            }

            if ((r == 0 && g == 120 && b == 215) || /* Windows 11 */ (r == 0 && g == 120 && b == 212))
            {
                // Main Blue Color for Buttons, Comboboxes, etc.
                pPixel[2] = GetRValue(accent);
                pPixel[1] = GetGValue(accent);
                pPixel[0] = GetBValue(accent);
            }
            else if (r == 0 && g == 122 && b == 217)
            {
                // Trackbar Thumb (DARKER BLUE)
                pPixel[2] = GetRValue(accentLight1);
                pPixel[1] = GetGValue(accentLight1);
                pPixel[0] = GetBValue(accentLight1);
            }
            else if ((r == 229 && g == 241 && b == 251) || /* Windows 11 */ (r == 216 && g == 230 && b == 241))
            {
                // Hovered Button (DARK BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 216 && g == 234 && b == 249)
            {
                // Tab (LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 204 && g == 228 && b == 247)
            {
                // Pressed Button (DARKER BLUE)
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }
            else if ((r == 0 && g == 56 && b == 102) || (r == 0 && g == 28 && b == 51))
            {
                // Toolbar Item / Item Corner (VERY LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if ((r == 0 && g == 27 && b == 50) || (r == 0 && g == 14 && b == 26))
            {
                // Explorer Item / Inactive Explorer Item Hover (VERY LIGHT BLUE)
                pPixel[2] = GetRValue(accentLight2) - 1;
                pPixel[1] = GetGValue(accentLight2) - 1;
                pPixel[0] = GetBValue(accentLight2) - 1;
            }
            else if (r == 217 && g == 235 && b == 249)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight3);
                pPixel[1] = GetGValue(accentLight3);
                pPixel[0] = GetBValue(accentLight3);
            }
            else if (r == 188 && g == 220 && b == 244)
            {
                // Items View Header
                pPixel[2] = GetRValue(accentLight2);
                pPixel[1] = GetGValue(accentLight2);
                pPixel[0] = GetBValue(accentLight2);
            }

            //pPixel[3] = 1;

            pPixel += 4;
        }
    }
    if (TEST)
    {
        std::cout << std::endl;
    }

    
    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    delete[] pBits;
    return TRUE;
}

int ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap);
}

void ModifyStyles()
{
    int i, j;

    ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, TMT_DIBDATA);
    
    ModifyStyle(VSCLASS_COMBOBOX, CP_DROPDOWNBUTTON, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_COMBOBOX, CP_BORDER, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_COMBOBOX, CP_READONLY, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_COMBOBOX, CP_DROPDOWNBUTTONRIGHT, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_COMBOBOX, CP_DROPDOWNBUTTONLEFT, 0, TMT_DIBDATA);

    for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
    {
        ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA);
    }
    for (i = TABP_TABITEM; i <= TABP_AEROWIZARDBODY; i++)
    {
        ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA);
    }
    for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
    {
        ModifyStyle(VSCLASS_TRACKBAR, i, 0, TMT_DIBDATA);
        j = 3;
        while (ModifyStyle(VSCLASS_TRACKBAR, i, 0, j)) {
            j += 1;
        }
    }
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, 2); // Windows 11?
    for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
    {
        ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA);
    }
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(VSCLASS_TOOLBAR, i, 0, TMT_DIBDATA);
    }
    for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
    {
        ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"SearchBox", 2, 0, TMT_DIBDATA); // Windows 11?
    ModifyStyle(L"BreadcrumbBar", 1, 0, TMT_DIBDATA);
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::TreeView", 1, i, TMT_DIBDATA);
    }
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::ListView", 1, i, TMT_DIBDATA);
    }
    ModifyStyle(L"PreviewPane", 1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel

    ModifyStyle(L"CommandModule", 1, 0, TMT_DIBDATA); // Windows 7 Explorer Command Bar
    for (i = 3; i <= 5; i++)
    {
        ModifyStyle(L"CommandModule", i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"ItemsView::Header", 1, 0, TMT_DIBDATA); // Explorer File Groups Header
    for (i = 1; i <= 2; i++)
    {
        ModifyStyle(L"ItemsView", 3, i, TMT_DIBDATA);
    }
    for (i = 1; i <= 16; i++)
    {
        ModifyStyle(L"ItemsView::ListView", 6, i, TMT_DIBDATA); // Explorer File Selection
    }

    for (i = 1; i <= 4; i++)
    {
        ModifyStyle(L"BB::Toolbar", i, 0, TMT_DIBDATA); // Explorer Breadcrumbs Highlight color
    }

    if (1) return;
    //ModifyStyle(VSCLASS_MENU, MENU_BARITEM, 0, TMT_DIBDATA); // ToDo: Make Bar Items Light Gray


    ModifyStyle(VSCLASS_MENU, MENU_POPUPITEM, 0, TMT_DIBDATA);
    ModifyStyle(VSCLASS_MENU, MENU_POPUPCHECKBACKGROUND, 0, TMT_DIBDATA);


    std::cout << "ModifyStyles: Done" << std::endl;
}

const int size = 4;
int main()
{
    InitAccentColors();

    ModifyStyles();

    int aElements[size] = {
        COLOR_ACTIVECAPTION,
        COLOR_HIGHLIGHT,
        COLOR_HOTLIGHT,
        COLOR_MENUHILIGHT
    };
    DWORD aOldColors[size];
    DWORD aNewColors[size];

    for (int i = 0; i < size; i++)
    {
        aOldColors[i] = GetSysColor(aElements[i]);
        aNewColors[i] = RGB(GetRValue(accent), GetGValue(accent), GetBValue(accent));
    }

    SetSysColors(size, aElements, aNewColors);

}
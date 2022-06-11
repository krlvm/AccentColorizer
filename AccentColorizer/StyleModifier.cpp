#include "StyleModifier.h"
#include "BitmapHelper.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"
#include <VersionHelpers.h>

int hsvAccentH;

bool colorizeMenus;
bool colorizeProgressBar;

void StandardBitmapHandler(int* r, int* g, int* b, int* a) {
    rgb rgbVal = { *r, *g, *b };
    hsv hsvVal = rgb2hsv(rgbVal);

    hsvVal.h = hsvAccentH;

    rgbVal = hsv2rgb(hsvVal);

    *r = rgbVal.r;
    *g = rgbVal.g;
    *b = rgbVal.b;
}

bool ModifyStyle(LPCWSTR pszClassList, int iPartId, int iStateId, int iPropId)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap, StandardBitmapHandler);
}

void ModifyStyles() {
    int i, j, k;

    ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    for (j = 1; j <= 7; j++) {
        ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, j);
        ModifyStyle(VSCLASS_BUTTON, BP_RADIOBUTTON, 0, j);
    }
    for (j = 1; j <= 3; j++) {
        ModifyStyle(VSCLASS_BUTTON, BP_GROUPBOX, 0, j);
    }

    for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
    {
        ModifyStyle(VSCLASS_COMBOBOX, i, 0, TMT_DIBDATA);
    }
    for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
    {
        ModifyStyle(VSCLASS_EDIT, i, 0, TMT_DIBDATA);
    }
    for (i = TABP_TABITEM; i <= TABP_TOPTABITEMBOTHEDGE; i++)
    {
        ModifyStyle(VSCLASS_TAB, i, 0, TMT_DIBDATA);
    }
    for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
    {
        for (j = 1; j <= 7; j++)
        {
            ModifyStyle(VSCLASS_TRACKBAR, i, 0, j);
            ModifyStyle(VSCLASS_TRACKBAR, i, 0, j);
        }
    }
    for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
    {
        ModifyStyle(VSCLASS_LISTBOX, i, 0, TMT_DIBDATA);
    }
    for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
    {
        ModifyStyle(VSCLASS_SPIN, i, 0, TMT_DIBDATA);
    }
    ModifyStyle(VSCLASS_HEADERSTYLE, HP_HEADERITEM, 0, TMT_DIBDATA);
    for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
    {
        ModifyStyle(L"Toolbar", i, 1, TMT_DIBDATA);
        ModifyStyle(L"ExplorerMenu::Toolbar", i, 1, TMT_DIBDATA);
        ModifyStyle(L"Alternate::Toolbar", i, 1, TMT_DIBDATA);
        ModifyStyle(L"Communications::Toolbar", i, 1, TMT_DIBDATA);
        ModifyStyle(L"InfoPaneToolbar::Toolbar", i, 1, TMT_DIBDATA);
    }
    ModifyStyle(L"BreadcrumbBar", 1, 0, TMT_DIBDATA);
    for (i = 1; i <= 6; i++)
    {
        for (j = 1; j <= 2; j++)
        {
            ModifyStyle(L"Explorer::TreeView", i, j, TMT_DIBDATA);
        }
    }
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 16; j++)
        {
            ModifyStyle(L"Explorer::ListView", i, j, TMT_DIBDATA);
        }
    }
    ModifyStyle(L"PreviewPane", 1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel

    for (i = 1; i <= 11; i++)
    {
        if (i == 8) continue;
        ModifyStyle(L"CommandModule", i, 0, TMT_DIBDATA);
        ModifyStyle(L"CommandModule", i, 1, TMT_DIBDATA);
    }
    ModifyStyle(L"ItemsView::Header", 1, 0, TMT_DIBDATA); // Explorer File Groups Header
    for (i = 1; i <= 7; i++)
    {
        ModifyStyle(L"ItemsView", 3, i, TMT_DIBDATA);
    }
    for (i = 1; i <= 16; i++)
    {
        for (j = 1; j <= 16; j++)
        {
            ModifyStyle(L"ItemsView::Header", i, j, TMT_DIBDATA);
            ModifyStyle(L"ItemsView::ListView", i, j, TMT_DIBDATA); // Explorer File Selection
        }
    }

    for (i = 8; i <= 9; i++)
    {
        for (j = 1; j <= 7; j++)
        {
            for (k = 1; k <= 7; k++)
            {
                ModifyStyle(L"ItemsView::ListView", i, j, k);
                ModifyStyle(L"Explorer::ListView", i, j, k);
                ModifyStyle(L"ListView", i, j, k);
            }
        }
    }
    for (j = 1; j <= 7; j++)
    {
        for (k = 1; k <= 7; k++)
        {
            ModifyStyle(L"Explorer::TreeView", 4, j, k);
        }
    }

    for (i = 1; i <= 4; i++)
    {
        ModifyStyle(L"BB::Toolbar", i, 0, TMT_DIBDATA); // Explorer Breadcrumbs Highlight color
    }

    ModifyStyle(L"Go::Toolbar", 1, 1, TMT_DIBDATA);
    ModifyStyle(L"InactiveGo::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"MaxGo::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"LVPopup::Toolbar", 1, 1, TMT_DIBDATA);
    ModifyStyle(L"LVPopupBottom::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"InactiveBB::Toolbar", 3, 1, TMT_DIBDATA);
    for (j = 1; j <= 6; j++)
    {
        ModifyStyle(L"InactiveBB::Toolbar", 4, j, j);
        ModifyStyle(L"InactiveBB::Toolbar", 4, j, TMT_DIBDATA);
        ModifyStyle(L"InactiveBBComposited::Toolbar", 4, j, j);
        ModifyStyle(L"InactiveBBComposited::Toolbar", 4, j, TMT_DIBDATA);
    }

    ModifyStyle(L"DragDrop", 7, 0, TMT_DIBDATA);
    ModifyStyle(L"Header", 1, 0, TMT_DIBDATA);

    for (j = 1; j <= 7; j++)
    {
        ModifyStyle(L"PAUSE", 1, 0, j);
    }

    for (i = 1; i <= 8; i++)
    {
        ModifyStyle(L"Tab", i, 1, TMT_DIBDATA);
    }


    // Explorer / Legacy Shell Date Picker
    for (i = 1; i <= 4; i++)
    {
        ModifyStyle(VSCLASS_MONTHCAL, i, 0, TMT_DIBDATA);
        ModifyStyle(VSCLASS_MONTHCAL, i, 1, TMT_DIBDATA);
    }
    for (j = 1; j <= 6; j++)
    {
        ModifyStyle(VSCLASS_MONTHCAL, MC_GRIDCELLBACKGROUND, j, TMT_DIBDATA);
    }
    for (i = 1; i <= 2; i++)
    {
        for (j = 0; j <= 1; j++)
        {
            ModifyStyle(L"DatePicker", i, j, 1);
            ModifyStyle(L"DatePicker", i, j, TMT_DIBDATA);
        }
    }

    ModifyStyle(L"Rebar", 6, 0, 2);
    for (i = 4; i <= 6; i++) {
        ModifyStyle(L"Rebar", i, 1, TMT_DIBDATA);
        ModifyStyle(L"Rebar", i, 1, TMT_DIBDATA);
    }
    
    for (j = 0; j <= 9; j++)
    {
        ModifyStyle(L"Desktop::ListView", 1, j, TMT_DIBDATA); // Desktop icons
    }

    for (i = 0; i <= 10; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            for (k = 0; k <= 10; k++)
            {
                ModifyStyle(L"TreeView", i, j, k);
                ModifyStyle(L"Navigation", i, j, k);
            }
        }
    }


    for (j = 1; j <= 7; j++)
    {
        for (k = 1; k <= 7; k++)
        {
            ModifyStyle(L"SearchBox", 2, j, k);
            ModifyStyle(L"SearchBoxComposited::SearchBox", 2, j, k);
            ModifyStyle(L"SearchButton::Toolbar", 3, j, k);
            ModifyStyle(L"SearchButton::Toolbar", 4, j, k);
        }
    }

    if (colorizeMenus)
    {
        ModifyStyle(L"Menu", 14, 0, TMT_DIBDATA);
        ModifyStyle(L"Menu", 13, 0, TMT_DIBDATA);
        ModifyStyle(L"Menu", 12, 0, TMT_DIBDATA);
        ModifyStyle(L"Menu", 8, 0, TMT_DIBDATA);
        ModifyStyle(L"Menu", 7, 0, TMT_DIBDATA);
    }

    if (colorizeProgressBar)
    {
        for (i = 3; i <= 10; i++)
        {
            ModifyStyle(L"Progress", i, 1, TMT_DIBDATA);
            ModifyStyle(L"Indeterminate::Progress", i, 1, TMT_DIBDATA);
        }
        ModifyStyle(L"Progress", 5, 4, TMT_DIBDATA);
        ModifyStyle(L"AB::AddressBand", 1, 1, TMT_DIBDATA);
    }

    /** Tweaks for legacy components **/

    ModifyStyle(L"Communications::Rebar", 6, 0, TMT_DIBDATA);

    ModifyStyle(L"StartPanel", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"StartMenu::Toolbar", 10, 1, TMT_DIBDATA);
    ModifyStyle(L"StartMenu::Toolbar", 12, 1, TMT_DIBDATA);

    for (i = 1; i <= 38; i++)
    {
        ModifyStyle(L"StartPanelPriv", i, 0, TMT_DIBDATA);
        ModifyStyle(L"StartPanelComposited::StartPanelPriv", i, 0, TMT_DIBDATA);
    }

    if (!IsWindows8OrGreater())
    {
        for (i = 1; i <= 8; i++)
        {
            ModifyStyle(L"TaskDialog", 13, i, TMT_DIBDATA);
        }
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 12; j++)
            {
                for (k = 1; k <= 7; k++)
                {
                    ModifyStyle(L"Header", i, j, k);
                    ModifyStyle(L"ItemsView::Header", i, j, k);
                }
            }
        }
    }
}

void ModifyStyles(COLORREF accentColor)
{
    rgb rgbAccent = { GetRValue(accentColor), GetGValue(accentColor), GetBValue(accentColor) };
    hsv hsvAccent = rgb2hsv(rgbAccent);
    hsvAccentH = hsvAccent.h;

    ModifyStyles();
}
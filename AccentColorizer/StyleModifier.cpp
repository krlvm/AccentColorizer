#include "StyleModifier.h"
#include "BitmapHelper.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"

void StandardBitmapHandler(int* r, int* g, int* b, int* a) {
    rgb rgbOriginal = { *r, *g, *b };
    rgb rgbAccent = { GetRValue(accent), GetGValue(accent), GetBValue(accent) };

    hsv hsvOriginal = rgb2hsv(rgbOriginal);
    hsv hsvAccent = rgb2hsv(rgbAccent);

    hsvOriginal.h = hsvAccent.h;

    rgb rgbNew = hsv2rgb(hsvOriginal);

    *r = rgbNew.r;
    *g = rgbNew.g;
    *b = rgbNew.b;
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
    int i, j;

    ModifyStyle(VSCLASS_BUTTON, BP_PUSHBUTTON, 0, TMT_DIBDATA);
    for (j = 1; j <= 7; j++) {
        ModifyStyle(VSCLASS_BUTTON, BP_CHECKBOX, 0, j);
    }
    for (j = 1; j <= 7; j++) {
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
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::TreeView", 1, i, TMT_DIBDATA);
    }
    for (i = 2; i <= 6; i++)
    {
        ModifyStyle(L"Explorer::ListView", 1, i, TMT_DIBDATA);
    }
    ModifyStyle(L"PreviewPane", 1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel

    ModifyStyle(L"CommandModule", 1, 0, TMT_DIBDATA);
    for (i = 1; i <= 10; i++)
    {
        ModifyStyle(L"CommandModule", i, 0, TMT_DIBDATA);
    }
    ModifyStyle(L"ItemsView::Header", 1, 0, TMT_DIBDATA); // Explorer File Groups Header
    for (i = 1; i <= 7; i++)
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

    ModifyStyle(L"Go::Toolbar", 1, 1, TMT_DIBDATA);
    ModifyStyle(L"InactiveGo::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"MaxGo::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"LVPopup::Toolbar", 1, 1, TMT_DIBDATA);
    ModifyStyle(L"LVPopupBottom::Toolbar", 1, 1, TMT_DIBDATA);

    ModifyStyle(L"InactiveBB::Toolbar", 3, 1, TMT_DIBDATA);
    for (j = 1; j <= 6; j++) {
        ModifyStyle(L"InactiveBB::Toolbar", 4, j, j);
        ModifyStyle(L"InactiveBB::Toolbar", 4, j, TMT_DIBDATA);
        ModifyStyle(L"InactiveBBComposited::Toolbar", 4, j, j);
        ModifyStyle(L"InactiveBBComposited::Toolbar", 4, j, TMT_DIBDATA);
    }

    ModifyStyle(L"DragDrop", 7, 0, TMT_DIBDATA);
    ModifyStyle(L"Header", 1, 0, TMT_DIBDATA);

    for (i = 1; i <= 3; i++)
    {
        for (j = 1; j <= 7; j++)
        {
            ModifyStyle(L"Navigation", i, 0, j);
        }
    }

    for (j = 1; j <= 7; j++)
    {
        ModifyStyle(L"PAUSE", 1, 0, j);
    }

    for (i = 1; i <= 8; i++)
    {
        ModifyStyle(L"Tab", i, 1, TMT_DIBDATA);
    }

    for (i = 1; i <= 2; i++)
    {
        ModifyStyle(L"DatePicker", i, 0, 1);
    }

    for (j = 0; j <= 6; j++)
    {
        ModifyStyle(L"Desktop::ListView", 1, j, j); // Desktop icons
    }

    ModifyStyle(L"Rebar", 6, 0, 2);
    for (i = 4; i <= 6; i++) {
        ModifyStyle(L"Rebar", i, 1, 2);
        ModifyStyle(L"Rebar", i, 1, 2);
    }
}
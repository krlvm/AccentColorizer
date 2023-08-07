#include "StyleModifier.h"
#include "BitmapHelper.h"
#include "ColorHelper.h"
#include "AccentColorHelper.h"
#include "SystemHelper.h"

bool g_bColorizeMenus;
bool g_bColorizeProgressBar;

HTHEME hTheme = nullptr;

void StandardBitmapPixelHandler(int& r, int& g, int& b, int& a)
{
	rgb_t rgbVal = { r, g, b };
	hsv_t hsvVal = rgb2hsv(rgbVal);

	hsvVal.h = g_hsvAccentH;

	rgbVal = hsv2rgb(hsvVal);

	r = rgbVal.r;
	g = rgbVal.g;
	b = rgbVal.b;
}

void SetCurrentTheme(LPCWSTR pszClassList)
{
	if (hTheme)
	{
		CloseThemeData(hTheme);
	}

	hTheme = OpenThemeData(NULL, pszClassList);
}

bool ModifyStyle(int iPartId, int iStateId, int iPropId)
{
	HBITMAP hBitmap;
	GetThemeBitmap(hTheme, iPartId, iStateId, iPropId, GBF_DIRECT, &hBitmap);
	return IterateBitmap(hBitmap, StandardBitmapPixelHandler);
}

///
/// At first glance, such refactoring looks useless,
/// premature and counterproductive, but
/// it speeded up the colorization four times,
/// i.e. tenths of a second
///
void ModifyStyles()
{
	int i, j, k;
	//


	SetCurrentTheme(VSCLASS_BUTTON);
	//
	ModifyStyle(BP_PUSHBUTTON, 0, TMT_DIBDATA);
	for (j = 1; j <= 7; j++)
	{
		ModifyStyle(BP_CHECKBOX, 0, j);
		ModifyStyle(BP_RADIOBUTTON, 0, j);
	}
	for (j = 1; j <= 3; j++)
	{
		ModifyStyle(BP_GROUPBOX, 0, j);
	}


	SetCurrentTheme(VSCLASS_COMBOBOX);
	//
	for (i = CP_DROPDOWNBUTTON; i <= CP_DROPDOWNBUTTONLEFT; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_EDIT);
	//
	for (i = EP_EDITBORDER_NOSCROLL; i <= EP_EDITBORDER_HVSCROLL; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_TAB);
	//
	for (i = TABP_TABITEM; i <= TABP_TOPTABITEMBOTHEDGE; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_TRACKBAR);
	//
	for (i = TKP_THUMB; i <= TKP_THUMBRIGHT; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			ModifyStyle(i, 0, j);
			ModifyStyle(i, 0, j);
		}
	}


	SetCurrentTheme(VSCLASS_LISTBOX);
	//
	for (i = LBCP_BORDER_HSCROLL; i <= LBCP_ITEM; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_SPIN);
	//
	for (i = SPNP_UP; i <= SPNP_DOWNHORZ; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_HEADERSTYLE);
	//
	ModifyStyle(HP_HEADERITEM, 0, TMT_DIBDATA);


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"ExplorerMenu::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"Alternate::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"Communications::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"InfoPaneToolbar::Toolbar");
	//
	for (i = TP_BUTTON; i <= TP_SPLITBUTTONDROPDOWN; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"BreadcrumbBar");
	//
	ModifyStyle(1, 0, TMT_DIBDATA);


	SetCurrentTheme(L"Explorer::TreeView");
	//
	for (i = 1; i <= 6; i++)
	{
		for (j = 1; j <= 2; j++)
		{
			ModifyStyle(i, j, TMT_DIBDATA);
		}
	}


	SetCurrentTheme(L"Explorer::ListView");
	//
	for (i = 1; i <= 10; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			ModifyStyle(i, j, TMT_DIBDATA);
		}
	}


	SetCurrentTheme(L"PreviewPane");
	//
	ModifyStyle(1, 1, TMT_DIBDATA); // Windows Vista/7 Explorer Bottom Details Panel


	SetCurrentTheme(L"CommandModule");
	//
	for (i = 1; i <= 11; i++)
	{
		if (i == 8) continue;
		ModifyStyle(i, 0, TMT_DIBDATA);
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"ItemsView");
	//
	for (i = 1; i <= 7; i++)
	{
		ModifyStyle(3, i, TMT_DIBDATA);
	}

	
	SetCurrentTheme(L"ItemsView::Header");
	//
	ModifyStyle(1, 0, TMT_DIBDATA); // Explorer File Groups Header
	for (i = 1; i <= 16; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			ModifyStyle(i, j, TMT_DIBDATA);
		}
	}


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"ItemsView::ListView");
	//
	for (i = 1; i <= 16; i++)
	{
		for (j = 1; j <= 16; j++)
		{
			ModifyStyle(i, j, TMT_DIBDATA); // Explorer File Selection
		}
	}
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"ListView");
	//
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"Explorer::ListView");
	//
	for (i = 8; i <= 9; i++)
	{
		for (j = 1; j <= 7; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"Explorer::TreeView");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(4, j, k);
		}
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"BB::Toolbar");
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA); // Explorer Breadcrumbs Highlight color
	}

	/////////////////////////////////////////////////////
	SetCurrentTheme(L"Go::Toolbar");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);


	SetCurrentTheme(L"InactiveGo::Toolbar");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"MaxGo::Toolbar");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"LVPopup::Toolbar");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);


	SetCurrentTheme(L"LVPopupBottom::Toolbar");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);
	/////////////////////////////////////////////////////



	/////////////////////////////////////////////////////
	SetCurrentTheme(L"InactiveBB::Toolbar");
	//
	ModifyStyle(3, 1, TMT_DIBDATA);
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(4, j, j);
		ModifyStyle(4, j, TMT_DIBDATA);
	}


	SetCurrentTheme(L"InactiveBBComposited::Toolbar");
	//
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(4, j, j);
		ModifyStyle(4, j, TMT_DIBDATA);
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"DragDrop");
	//
	ModifyStyle(7, 0, TMT_DIBDATA);
	ModifyStyle(8, 0, TMT_DIBDATA);


	SetCurrentTheme(L"Header");
	//
	ModifyStyle(1, 0, TMT_DIBDATA);


	SetCurrentTheme(L"PAUSE");
	//
	for (j = 1; j <= 7; j++)
	{
		ModifyStyle(1, 0, j);
	}


	SetCurrentTheme(L"Tab");
	//
	for (i = 1; i <= 8; i++)
	{
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(VSCLASS_MONTHCAL); // Explorer / Legacy Shell Date Picker
	//
	for (i = 1; i <= 4; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
		ModifyStyle(i, 1, TMT_DIBDATA);
	}
	for (j = 1; j <= 6; j++)
	{
		ModifyStyle(MC_GRIDCELLBACKGROUND, j, TMT_DIBDATA);
	}


	SetCurrentTheme(L"DatePicker");
	//
	for (i = 1; i <= 2; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			ModifyStyle(i, j, 1);
			ModifyStyle(i, j, TMT_DIBDATA);
		}
	}


	SetCurrentTheme(L"Rebar");
	//
	ModifyStyle(6, 0, 2);
	for (i = 4; i <= 6; i++) {
		ModifyStyle(i, 1, TMT_DIBDATA);
		ModifyStyle(i, 1, TMT_DIBDATA);
	}


	SetCurrentTheme(L"Desktop::ListView");
	//
	for (j = 0; j <= 9; j++)
	{
		ModifyStyle(1, j, TMT_DIBDATA); // Desktop icons
	}

	/////////////////////////////////////////////////////
	SetCurrentTheme(L"TreeView");
	//
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}


	SetCurrentTheme(L"Navigation");
	//
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				ModifyStyle(i, j, k);
			}
		}
	}
	/////////////////////////////////////////////////////


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"CopyClose");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(1, j, k);
		}
	}


	SetCurrentTheme(L"SearchBox");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(2, j, k);
		}
	}


	SetCurrentTheme(L"SearchBoxComposited::SearchBox");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(2, j, k);
		}
	}


	SetCurrentTheme(L"SearchButton::Toolbar");
	//
	for (j = 1; j <= 7; j++)
	{
		for (k = 1; k <= 7; k++)
		{
			ModifyStyle(3, j, k);
			ModifyStyle(4, j, k);
		}
	}
	/////////////////////////////////////////////////////


	SetCurrentTheme(L"TaskbandExtendedUI");	// Taskbar Thumbnail Media Controls
	//
	for (i = (g_winver >= WIN_10 ? 6 : 8); i <= (g_winver >= WIN_10 ? 9 : 11); i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
		ModifyStyle(i, 1, TMT_DIBDATA);
	}

	if (g_bColorizeMenus)
	{
		SetCurrentTheme(L"Menu");
		//
		ModifyStyle(14, 0, TMT_DIBDATA);
		ModifyStyle(13, 0, TMT_DIBDATA);
		ModifyStyle(12, 0, TMT_DIBDATA);
		ModifyStyle(8, 0, TMT_DIBDATA);
		ModifyStyle(7, 0, TMT_DIBDATA);

		// Menu Checkbox
		for (j = 0; j <= 7; j++)
		{
			for (k = 0; k <= 7; k++)
			{
				ModifyStyle(11, j, k);
			}
		}
	}

	if (g_bColorizeProgressBar)
	{
		SetCurrentTheme(L"Progress");
		//
		ModifyStyle(5, 4, TMT_DIBDATA);
		for (i = 3; i <= 10; i++)
		{
			ModifyStyle(i, 1, TMT_DIBDATA);
		}


		SetCurrentTheme(L"Indeterminate::Progress");
		//
		for (i = 3; i <= 10; i++)
		{
			ModifyStyle(i, 1, TMT_DIBDATA);
		}


		SetCurrentTheme(L"AB::AddressBand");
		//
		ModifyStyle(1, 1, TMT_DIBDATA);
	}

	/** Tweaks for legacy components **/

	SetCurrentTheme(L"Communications::Rebar");
	//
	ModifyStyle(6, 0, TMT_DIBDATA);


	SetCurrentTheme(L"StartPanel");
	//
	ModifyStyle(1, 1, TMT_DIBDATA);


	SetCurrentTheme(L"StartMenu::Toolbar");
	//
	ModifyStyle(10, 1, TMT_DIBDATA);
	ModifyStyle(12, 1, TMT_DIBDATA);


	/////////////////////////////////////////////////////
	SetCurrentTheme(L"StartPanelPriv");
	//
	for (i = 1; i <= 38; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}


	SetCurrentTheme(L"StartPanelComposited::StartPanelPriv");
	//
	for (i = 1; i <= 38; i++)
	{
		ModifyStyle(i, 0, TMT_DIBDATA);
	}
	/////////////////////////////////////////////////////

	if (g_winver < WIN_8)
	{
		SetCurrentTheme(L"TaskDialog");
		//
		for (i = 1; i <= 8; i++)
		{
			ModifyStyle(13, i, TMT_DIBDATA);
		}


		/////////////////////////////////////////////////////
		SetCurrentTheme(L"Header");
		//
		for (i = 1; i <= 7; i++)
		{
			for (j = 1; j <= 12; j++)
			{
				for (k = 1; k <= 7; k++)
				{
					ModifyStyle(i, j, k);
				}
			}
		}


		SetCurrentTheme(L"ItemsView::Header");
		//
		for (i = 1; i <= 7; i++)
		{
			for (j = 1; j <= 12; j++)
			{
				for (k = 1; k <= 7; k++)
				{
					ModifyStyle(i, j, k);
				}
			}
		}
		/////////////////////////////////////////////////////


		SetCurrentTheme(L"ScrollBar");
		//
		for (i = 1; i <= 10; i++)
		{
			for (k = 1; k <= 4; k++)
			{
				ModifyStyle(i, 0, k);
			}
		}
	}

	//
	CloseThemeData(hTheme);
	hTheme = nullptr;
}
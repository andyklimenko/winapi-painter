// WinapiPainter.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WinapiPainter.h"
#include <CommCtrl.h>
#include <memory>

#include "Controller\DrawerFactory.h"
#include "View\BaseDrawer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HIMAGELIST g_hImageList = NULL;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND CreateToolbarFromResource(HWND hWndParent);

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
    LoadStringW(hInstance, IDC_WINAPIPAINTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPAINTER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPAINTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIPAINTER);
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

   HWND hWnd = CreateWindowEx(
	   WS_EX_CLIENTEDGE,
	   szWindowClass,
	   szTitle,
	   WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT,
	   CW_USEDEFAULT,
	   640,
	   480,
	   NULL,
	   NULL,
	   hInstance,
	   NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   CreateToolbarFromResource(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

std::shared_ptr<BaseDrawer> pDrawer;
HDC g_Hdc = nullptr;
bool capturingCursor = false;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_DRAW_LINE:
				pDrawer.reset(DrawerFactory::CreateDrawer(LinePrimitive));
				break;
			case ID_DRAW_RECTANGLE:
				pDrawer.reset(DrawerFactory::CreateDrawer(RectanglePrimitive));
				break;
			case ID_DRAW_ELLIPSE:
				pDrawer.reset(DrawerFactory::CreateDrawer(EllipsePrimitive));
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		g_Hdc = GetDC(hWnd);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (pDrawer)
			{
				pDrawer->Draw(hdc);
			}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		ReleaseDC(hWnd, g_Hdc);
		g_Hdc = nullptr;
        PostQuitMessage(0);
        break;

	case WM_LBUTTONDOWN:
		if (pDrawer)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			pDrawer->setFrom(pt);
			capturingCursor = true;
		}

		break;
	case WM_LBUTTONUP:
		if (pDrawer && capturingCursor)
		{
			capturingCursor = false;
			InvalidateRect(hWnd, nullptr, FALSE);
		}
		break;
	case WM_MOUSEMOVE:
		if (pDrawer && capturingCursor)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			pDrawer->setTo(pt);
		}
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

HWND CreateToolbarFromResource(HWND hWndParent)
{
	// Declare and initialize local constants.
	const int ImageListID = 0;
	const int numButtons = 3;
	const int bitmapSize = 16;

	const DWORD buttonStyles = BTNS_AUTOSIZE | BTNS_CHECKGROUP;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
		hWndParent, NULL, hInst, NULL);
	if (hWndToolbar == NULL)
		return NULL;

	// Create the image list.
	g_hImageList = ImageList_Create(bitmapSize, bitmapSize, // Dimensions of individual bitmaps.
		ILC_COLOR16 | ILC_MASK, // Ensures transparent background.
		numButtons, 0);
		
	SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)ImageListID, (LPARAM)g_hImageList); // Set the image list.
	SendMessage(hWndToolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_SMALL_COLOR,(LPARAM)HINST_COMMCTRL); // Load the button images.

	// Load the text from a resource.
	// In the string table, the text for all buttons is a single entry that 
	// appears as "~New~Open~Save~~". The separator character is arbitrary, 
	// but it must appear as the first character of the string. The message 
	// returns the index of the first item, and the items are numbered 
	// consecutively.

	LRESULT iNew = SendMessage(hWndToolbar, TB_ADDSTRING, (WPARAM)hInst, (LPARAM)IDS_TOOLBAR_TEXT);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

	TBBUTTON tbButtons[numButtons] =
	{
		{ MAKELONG(IDI_ICON_LINE,  ImageListID),	ID_DRAW_LINE,  TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, iNew },
		{ MAKELONG(IDI_ICON_RECT, ImageListID),		ID_DRAW_RECTANGLE, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, iNew + 1 },
		{ MAKELONG(IDI_ICON_ELLIPSE, ImageListID),	ID_DRAW_ELLIPSE, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, iNew + 2 }
	};

	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hWndToolbar, TRUE);

	return hWndToolbar;
}

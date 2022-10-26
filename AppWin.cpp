#include "AppWin.h"

AppWin::AppWin()
{
}

AppWin::~AppWin()
{
}

void AppWin::onCreate(HWND hwnd)
{
	//create menu bar
	HMENU menu = CreateMenu();


	HMENU subMenuFile = CreateMenu();
	HMENU subMenuDebug = CreateMenu();

	AppendMenu(subMenuFile, MF_STRING, 6, L"Poggers");
	AppendMenu(subMenuFile, MF_STRING, 7, L"New");
	AppendMenu(subMenuFile, MF_STRING, 8, L"Open");
	AppendMenu(subMenuFile, MF_SEPARATOR, NULL, NULL);
	AppendMenu(subMenuFile, MF_STRING, 9, L"Exit");

	AppendMenu(subMenuDebug, MF_STRING, 10, L"Render Mode: NORMAL");
	AppendMenu(subMenuDebug, MF_STRING, 11, L"Render Mode: CUSTOM");
	AppendMenu(subMenuDebug, MF_SEPARATOR, NULL, NULL);
	AppendMenu(subMenuDebug, MF_STRING, 12, L"Console Print");

	AppendMenu(menu, MF_POPUP, (UINT_PTR) subMenuFile, L"File");

	AppendMenu(menu, MF_STRING, 2, L"Edit");
	AppendMenu(menu, MF_POPUP, (UINT_PTR)subMenuDebug, L"Debug");
	AppendMenu(menu, MF_STRING, 3, L"Egg");
	AppendMenu(menu, MF_STRING, 4, L"About");
	AppendMenu(menu, MF_STRING, 5, L"Help");

	SetMenu(hwnd, menu);

	//create window content
	HWND btn = CreateWindow(
		L"BUTTON",
		L"Test",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 
		10,
		100,
		25,
		hwnd,
		NULL,
		(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
		NULL
	);
}

//function used to determine if were in a CUSTOM context.
bool AppWin::AssertCustomRenderMode() {
	return render_mode == CUSTOM;
}

void AppWin::onUpdated()
{

}

void AppWin::onDestroy()
{
	Window::onDestroy();
}

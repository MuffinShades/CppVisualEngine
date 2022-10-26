#pragma once

//load visual style 6.0.0.0
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//h files
#include <windows.h>
#include <iostream>
#include <stdint.h>
#include <string>

//use the standard library
using namespace std;

//defenitions
#define i32 uint32_t;

//class
class Window
{
public:
	Window();

	int width;
	int height;
	int render_mode = 0x00;
	int CUSTOM = 0x01;
	int NORMAL = 0x00;

	bool init(const wchar_t* title);
	bool release();

	bool broadcast();

	bool isRunning();

	virtual void onCreate(HWND hwnd)=0;
	virtual void onUpdated()=0;
	virtual void onDestroy();

	void* memory_buffer;

	void RenderPixel(int x, int y, int color);
	void ClearScreenBuffer();

	BITMAPINFO bitmap_inf;

	HDC hdc;

	//width and height of window

	bool AssertCustomRenderMode();

	bool RenderScreenObjects();

	void SetRenderMode(int mode);

	bool mode_change = false;

	void winPaint();

	void* temp;

	~Window();

	//window buffer variables
protected:
		HWND m_hwnd;
		bool m_running=true;
private:
	int* pixel;
	bool modeSwitch = false;
};


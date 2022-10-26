#include "Window.h"

/**
 * Low-Level Code for creating a Window
 * @param {window} current window
 * @param {m_running} Determines whether the window is running or not.
 * @author {James Weigand (muffinshades)}
 * 
 * This class is just responsible for loading a window.
 *	Also handles basic pixel rendering
 *	This pixel rendering is provided to the Graphics class that handles more advanced rendering
 */


//create a pointer to a window
Window* window = nullptr;

//variable for whether the window is running or not
bool m_running = true;


//set default render modes
int CUSTOM = 0x01;
int NORMAL = 0x00;
int render_mode = NORMAL;

//initializer
Window::Window() {
	cout << "Window Low-Level Code: v1.0.0" << endl;
}

void Window::onCreate(HWND hwnd) {

}

//Function that handles window events
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	//handles message
	switch (msg) {

	//call built-in virtual functions if the window is created | good for loading save data
	case WM_CREATE:
	{
		//call virtual on create function
		window->onCreate(hwnd);
		break;
	}

	case WM_COMMAND:
	{
		//handle command requests
		switch (wparam) {

		//title bar functionality

		//EGG option
		case 3: {
			MessageBeep(MB_OK);
			break;
		}

		//help option
		case 5: {
			MessageBox(hwnd, L"This is the help box. Idk what to put here. \n Instagram: @muffinshades \n Twitter: @muffinshades", L"Help", 0);
			break;
		}

		case 10: {
			window->SetRenderMode(NORMAL);
			break;
		}

		case 11: {
			window->SetRenderMode(CUSTOM);
			break;
		}

		case 12: {
			cout << "Window Addr: " << &window << endl;
			break;
		}
		}
		break;
	}

	//call built-in virtual functions if the window is created | good for saving data
	case WM_DESTROY:
	{
		//remove the window
		window->onDestroy();

		//return 0 to the debug console
		::PostQuitMessage(0);
		break;
	}

	//Handle other events normaly
	default:

		//call defalt window operation if it's no overwritten
		return ::DefWindowProc(hwnd,msg,wparam,lparam);
	}

	return NULL;
}

/**
 *
 * Window Initializer
 * 
 * Creates a window
 * 
 * -----------------
 * Window Class: WinClass
 * 
 */
bool Window::init(const wchar_t* title) {
	WNDCLASSEX wc;


	const wchar_t* class_name = L"WinClass";

	//set properties for window class

	//CLASS NAME IS "WinClass"
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = class_name;
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;


	//register the window class
	if (!::RegisterClassEx(&wc)) {

		//return false if registration fails
		return false;
	}

	//set our local window pointer
	if (!window) {
		window = this;
	}

	//create the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, class_name, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);

	//create device context
	hdc = GetDC(m_hwnd);

	//get the width and height of the window
	RECT rect;
	GetClientRect(m_hwnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	//allocate screen memory
	int sz = width * height;
	memory_buffer = VirtualAlloc(
		0,
		sz * sizeof(unsigned int),
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE
	);

	

	//create bitmap info and set the headers
	bitmap_inf.bmiHeader.biSize = sizeof(bitmap_inf.bmiHeader);
	bitmap_inf.bmiHeader.biWidth = width;
	bitmap_inf.bmiHeader.biHeight = height;
	bitmap_inf.bmiHeader.biPlanes = 1;
	bitmap_inf.bmiHeader.biBitCount = 32;
	bitmap_inf.bmiHeader.biCompression = BI_RGB;

	//return false if window creating failed
	if (!m_hwnd) {
		return false;
	}

	//show and update the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	//return
	return true;
}

/**
 * BROADCAST function
 * 
 * Listens and dispatches window requests
 * 
 */
bool Window::broadcast() {

	//current message
	MSG msg;

	//loop through all message requests
	while (::PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0) {

		//translate and dispatch the current message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//render to the screen the memory buffer
	if (render_mode == CUSTOM) {
		if (mode_change) {
			HBITMAP map = GetScreenBmp(hdc);
			GetDIBits(
				hdc,

			);
			mode_change = false;
		}

		//load the void* into the windows pixel memory using StretchDIBits
		StretchDIBits(
			hdc,
			0,
			0,
			width,
			height,
			0,
			0,
			width,
			height,
			memory_buffer,
			&bitmap_inf,
			DIB_RGB_COLORS,
			SRCCOPY
		);
	}
	else {
		//make sure its the first time clearning
		if (mode_change) {
			//clear on screen data
			StretchDIBits(
				hdc,
				0,
				0,
				width,
				height,
				0,
				0,
				width,
				height,
				NULL,
				NULL,
				DIB_RGB_COLORS,
				SRCCOPY
			);
			//reset mode_change
			mode_change = false;
		}
	}

	//buttom creation code

	//call update function
	window->onUpdated();

	//pause to release stress on cpu
	Sleep(1);

	return true;
}

//returns true or false based off of if the window is currently running or not
bool Window::isRunning() {
	return m_running;
}

//closes the window
bool Window::release() {
	if (m_hwnd) {
		if (!::DestroyWindow(m_hwnd)) {
			return false;
		}
	}

	return true;
}

//renders a single pixel to the screen
void Window::RenderPixel(int x, int y, int color) {
	if (memory_buffer && color && render_mode == CUSTOM) {
		//calculate pixel position in memory
		int ny = height - y;
		int p = (ny * width) + x;

		//access specific byte in memory
		unsigned int* pix = ((unsigned int*) memory_buffer) + (p);

		//set the value of the byte to the color
		*pix = color;
	}
}

//clears the render buffer
void Window::ClearScreenBuffer() {
	if (memory_buffer && width && height && render_mode == CUSTOM) {
		int sz = width * height;

		//delete old memory
		//save result in a variable to prevent memory leaks

		bool f = VirtualFree(
			memory_buffer,
			sz * sizeof(unsigned int),
			MEM_DECOMMIT
		);

		//re allocate new memory

		if (f) {
			memory_buffer = VirtualAlloc(
				0,
				sz * sizeof(unsigned int),
				MEM_RESERVE | MEM_COMMIT,
				PAGE_READWRITE
			);
		}
	}
}

//return whether or not the window is in custom mode or not
bool AssertCustomRenderMode() {
	return render_mode == CUSTOM;
}

//renders on screen objs
bool Window::RenderScreenObjects() {
	return true;
}

//sets the render mode | Excepts: CUSTOM or NORMAL
void Window::SetRenderMode(int mode) {
	mode_change = true;
	render_mode = mode;
}

//initializer
Window::~Window() {

}


//virtual functions
void Window::onUpdated() {

}

void Window::onDestroy() {
	m_running = false;
}
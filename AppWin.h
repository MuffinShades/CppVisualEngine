#pragma once
#include "Window.h";

#include <windows.h>
#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;

class AppWin: public Window
{
public:
	AppWin();



	~AppWin();

	// Inherited via Window
	virtual void onCreate(HWND hwnd) override;
	virtual void onUpdated() override;
	virtual void onDestroy() override;

	//custom render mode
	bool AssertCustomRenderMode();
};


#pragma once

#include "AppWin.h";
#include <iostream>

using namespace std;

class visual
{
public:
	void init(AppWin* win);
	void Draw(int x, int y, int r, int g, int b);
	void Draw(int x, int y);
	void FillRect(int x, int y, int w, int h);
	void SetColor(int r, int g, int b);
	void Clear();

	bool AssertDrawMode();

	int renderMode = 0x01;

	bool ld = false;

	//render color
	int v_color = 0x000000;

	string GetLocalVersion();

	string version = "v1.0.0";

protected:
	AppWin* _win;
};


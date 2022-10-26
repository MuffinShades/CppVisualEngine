#include "AppWin.h";
#include <iostream>
#include <Windows.h>
#include "visual.h";

using namespace std;

int main() {
	AppWin app;
	visual v;

	const wchar_t* title = L"Application";

	if (app.init(title)) {
		AppWin* app_ptr = (&app);

		//set current render mode to NORMAL
		app.SetRenderMode(0x00);

		v.init(app_ptr);

		v.SetColor(255, 0, 0);

		while (app.isRunning()) {
			app.broadcast();

			v.Clear();

			v.FillRect(100, 100, 100, 100);
		}
	}

	return 0;
}
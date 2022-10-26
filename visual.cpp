#include "visual.h"

/**
 * Basic 2d C++ visual library.
 * Coded by James Weigand on Oct. 24 2022
 * @author {James Weigand}
 */

//get the local version of the software
string visual::GetLocalVersion() {
	return version;
}

//load the visual class
void visual::init(AppWin* win) {
	if (!ld) {
		cout << "Visual.cpp Version" << GetLocalVersion() << endl;
		_win = win;
		ld = true;
	}
}

/**
 * Visual Draw Function
 * 
 * Draws a single pixel to the screen
 * Can specify a color or render the loaded color
 * @param {x} Position on the X axis where the pixel is
 * @param {y} Position on the Y axis where the pixel is
 * @param {r} Red Color of the pixel.
 * @param {g} Green Color of the pixel.
 * @param {b} Blue Color of the pixel.
 */
void visual::Draw(int x, int y, int r, int g, int b) {
	if (ld && _win) {
		if (_win->AssertCustomRenderMode()) {
			if (x >= 0 && y >= 0 && x < _win->width && y < _win->height) {
				//convert r, g, b value to a color
				int color = (r << 16) | (g << 8) | (b);
				//render to the screen
				_win->RenderPixel(x, y, color);
			}
			else {
				cout << "Out of Bounds Error!" << endl;
			}
		}
	}
	else {
		cout << "Error, visual libary has not been loaded with a window!" << endl;
	}
}

//Visual draw function part 2
//Uses the loaded color value
void visual::Draw(int x, int y) {
	if (ld && _win) {
		if (_win->AssertCustomRenderMode()) {
			if (x >= 0 && y >= 0 && x < _win->width && y < _win->height) {
				//render to the screen
				_win->RenderPixel(x, y, v_color);
			}
			else {
				cout << "Out of Bounds Error!" << endl;
			}
		}
	}
	else {

		//error dispatch
		cout << "Error, visual libary has not been loaded with a window!" << endl;
	}
}

/**
 * Visual Fill Rect Function
 * Takes in a x, y, width, and height values specifing the dimensions of the rectangle
 * The Color of the rectangles is determined by the current set color
 * @param {x} Start position on the X axis.
 * @param {y} Start position on the Y axis.
 * @param {w} Width of the Rectangle.
 * @param {h} Height of the Rectangle.
 */
void visual::FillRect(int x, int y, int w, int h) {
	if (ld && _win) {
		if (_win->AssertCustomRenderMode()) {
			int sx = x, sy = y, ex = x + w, ey = y + h;

			//clamp values
			if (sx < 0) sx = 0;
			if (ex < 0) ex = 0;
			if (sy < 0) sy = 0;
			if (ey < 0) ey = 0;

			if (sx > _win->width) sx = (_win->width - 1);
			if (ex > _win->width) ex = (_win->width - 1);
			if (sy > _win->height) sy = (_win->height - 1);
			if (ey > _win->height) ey = (_win->height - 1);

			//render rectangle
			for (int i = sx; i < ex; i++) {
				for (int j = sy; j < ey; j++) {
					visual::Draw(i, j);
				}
			}
		}
	}
	else {
		cout << "Error, visual libary has not been loaded with a window!" << endl;
	}
}

//sets the color
void visual::SetColor(int r, int g, int b) {

	//set render color

	v_color = (r << 16) | (g << 8) | (b);
}

//returns true if were drawing
bool visual::AssertDrawMode() {

	//determine if were in a drawing context.
	if (ld && _win) return _win->AssertCustomRenderMode();

	return false;
}

//Used to clear the screen
void visual::Clear() {
	//assert
	if (ld && _win && _win->AssertCustomRenderMode()) {

		//clear screen
		_win->ClearScreenBuffer();
	}
}
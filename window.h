#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
	XEvent event;

public:
	Xwindow(int width=800, int height=500);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	Xwindow(const Xwindow&) = delete;
	Xwindow &operator=(const Xwindow&) = delete;

	enum {White, Black, Red, Gray}; // Available colours.

	// Draws a line
	void drawRectangle(int, int, int, int, int colour = Black);

	// Draws a rectangle
	void fillRectangle(int, int, int, int, int colour=Black);

	// Draws a string
	void drawString(int, int, std::string msg);

	// Insert a image
	void putImage(int, int, const char*);

	// Clear window
	void clearWindow();

	// Clear area
	void clearArea(int x, int y, int width, int height);

	// return points
	std::vector<int> getPointSelected();

	// return command
	std::vector<int> getSelectedCommand();

	// return selected promotion piece
	int getSelectedPiece();
};

#endif

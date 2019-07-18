#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <png.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
	d = XOpenDisplay(NULL);
	if (d == NULL) {
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(
		d, RootWindow(d, s), 10, 10, width, height, 
		1, BlackPixel(d, s), WhitePixel(d, s)
	);
	XStoreName(d, w, "SORCERY");

	XSelectInput(d, w, ExposureMask | ButtonPressMask);

	Pixmap pix = XCreatePixmap(
		d, w, width, height, 
		DefaultDepth(d, DefaultScreen(d))
	);

	gc = XCreateGC(d, pix, 0, 0);

	// Set up colours.
	XColor xcolour;
	Colormap cmap;

	const size_t numColours = 4;
	char color_vals[numColours][10] = {
		"white", "black", "red", "gray"
	};

	cmap = DefaultColormap(d, DefaultScreen(d));
	
	for(unsigned int i = 0; i < numColours; ++i) {
		XParseColor(d, cmap, color_vals[i], &xcolour);
		XAllocColor(d, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(d, gc, colours[White]);

	 // Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	// map window and flush
	XMapRaised(d, w);
	XFlush(d);
	
	// wait 1 second for setup
	sleep(1);
}

Xwindow::~Xwindow() {
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XDrawRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void Xwindow::drawString(int x, int y, string msg) {
	XSetForeground(d, gc, colours[1]);
	XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
	XFlush(d);
}

void Xwindow::putImage(int x, int y, const char* filename) {
	FILE *file = fopen(filename, "r");
	if(!file){
		cout << filename << " Cannot open file" << endl;
	}
	
	char *data = NULL;

    png_struct *pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_info *pngInfo = NULL;

    int readFlag = PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND;
    int colorType = 0,
		interlaceMethod = 0,
		rowBytes = 0,
		bitDepth = 0;

    png_uint_32 index = 0,
				width = 0,
				height = 0;
    png_bytepp rowPointers = NULL;

    if (!pngPtr) {
        return;
    } else if (!(pngInfo = png_create_info_struct(pngPtr))) {
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        return;
    }
    if (setjmp(png_jmpbuf(pngPtr))) {
        png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
        return;
    }

    png_init_io(pngPtr, file);
    png_set_sig_bytes(pngPtr, 0);

    png_read_png(pngPtr, pngInfo, readFlag, NULL);
    png_get_IHDR(pngPtr, pngInfo, &width, &height,
                 &bitDepth, &colorType, &interlaceMethod,
                 NULL, NULL);

    rowBytes = png_get_rowbytes(pngPtr, pngInfo);
    data = (char*) malloc(rowBytes * height);
    rowPointers = png_get_rows(pngPtr, pngInfo);
	if (!data) {
        png_destroy_read_struct(&pngPtr, &pngInfo, NULL);
        return;
    }
    while (index < height) {
        memcpy(data + (index * rowBytes), rowPointers[index], rowBytes);
        ++index;
    }

	XImage *image = XCreateImage(d, CopyFromParent, DefaultDepth(d,s), ZPixmap,
        			0, data, width, height, 8, rowBytes);
    png_destroy_info_struct(pngPtr, &pngInfo);
    png_destroy_read_struct(&pngPtr, &pngInfo, NULL);

	XPutImage(d, w, gc, image, 0, 0, x, y, width, height);
	XDestroyImage(image);
	
	fclose(file);
	XFlush(d);
}

void Xwindow::clearWindow() {
	XClearWindow(d, w);
	XFlush(d);
}

void Xwindow::clearArea(int x, int y, int width, int height) {
	XClearArea(d, w, x, y, width, height, 0);
	XFlush(d);
}

vector<int> Xwindow::getPointSelected() {
	vector<int> pts;
	while(1) {
		XNextEvent(d, &event);
		switch (event.type){
			case ButtonPress:
				pts.emplace_back(event.xbutton.x);
				pts.emplace_back(event.xbutton.y);
				cout<<"X: "<<event.xbutton.x<<" Y:"<<event.xbutton.y << endl;
				XFlush(d);
				if (pts[0] < 390 || pts[0] > 710 || pts[1] < 90 || pts[1] > 410) {
					pts.clear();
				} else return pts;
			default:
				break;
		}
	}
	return pts;
}

vector<int> Xwindow::getSelectedCommand() {
	vector<int> pts;
	while(1) {
		XNextEvent(d, &event);
		switch (event.type){
			case ButtonPress:
				cout<<"SELECT COMMAND"<<endl;
				pts.emplace_back(event.xbutton.x);
				pts.emplace_back(event.xbutton.y);
				XFlush(d);

				if (!(pts[1] > 40 && pts[1] < 63 && pts[0] > 55 && pts[0] < 95) &&
					!(pts[1] > 40 && pts[1] < 63 && pts[0] > 100 && pts[0] < 150) &&
					!(pts[1] > 40 && pts[1] < 63 && pts[0] > 155 && pts[0] < 195) &&
					!(pts[1] > 73 && pts[1] < 96 && pts[0] > 55 && pts[0] < 135) &&
					!(pts[1] > 106 && pts[1] < 129 && pts[0] > 55 && pts[0] < 175) &&
					!(pts[1] > 106 && pts[1] < 129 && pts[0] > 200 && pts[0] < 280)
				) pts.clear();
				else return pts;
			default:
				break;
		}
	}
	return pts;
}

int Xwindow::getSelectedPiece() {
	vector<int> pts;
	while(1) {
		XNextEvent(d, &event);
		switch (event.type){
			case ButtonPress:
				cout << "SELECT PROMOT"<<endl;
				pts.emplace_back(event.xbutton.x);
				pts.emplace_back(event.xbutton.y);
				XFlush(d);
				if (!(pts[0] > 140 && pts[0] < 300) && !(pts[1] > 70 && pts[1] < 110)) {
					pts.clear();
				} else return pts[0];
			default:
				break;
		}
	}
	return 0;
}


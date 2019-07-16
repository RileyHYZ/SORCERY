#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
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

	XSelectInput(d, w, ExposureMask | KeyPressMask);

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
	// char **missingList;
    // int missingCount;
    // char *defString;
	// char *fontName = "-jis-fixed-medium-r-normal--16-110-100-100-c-160-jisx0208.1983-0";
    // XFontSet fontSet =
    //     XCreateFontSet(d, fontName,
    //                    &missingList, &missingCount, &defString);
    // if (fontSet == NULL) {
	// 	printf("Failed to create fontset\n");
	// 	return;
    // }
    // XFreeStringList(missingList);
	XFontSet fontset;
	char **missing_charsets;
	int num_missing_charsets;
	char *default_string;
	fontset = XCreateFontSet (d, "-*-*-*-*-*-*-16-*-*-*-*-*-*-*",
                        &missing_charsets, &num_missing_charsets,
                        &default_string);
        if ( num_missing_charsets > 0 ) {
                XFreeStringList (missing_charsets);
        }
	XSetForeground(d, gc, colours[1]);
	XmbDrawString(d, w, fontset, gc, x, y, msg.c_str(), msg.length());
	XFlush(d);
}

void TeardownPng (png_structp png, png_infop info)
{
        if (png) {
                png_infop *realInfo = (info? &info: NULL);
                png_destroy_read_struct (&png, realInfo, NULL);
        }
}
void LoadPng (FILE *file, unsigned char** data, char **clipData, unsigned int *width, unsigned int *height, unsigned int *rowbytes)
{
        size_t size = 0,  clipSize = 0;
        png_structp png = NULL;
        png_infop info = NULL;
        unsigned char **rowPointers = NULL;
        int depth = 0,
            colortype = 0,
            interlace = 0,
            compression = 0,
            filter = 0;
        unsigned clipRowbytes = 0;
png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
info = png_create_info_struct (png);
        png_init_io (png, file);
        png_read_info (png, info);
        png_get_IHDR (png, info, (png_uint_32*)width, (png_uint_32*)height, &depth, &colortype, &interlace, &compression, &filter);
        *rowbytes = png_get_rowbytes (png, info);
        if (colortype == PNG_COLOR_TYPE_RGB) {
                // X hates 24bit images - pad to RGBA
                png_set_filler (png, 0xff, PNG_FILLER_AFTER);
                *rowbytes = (*rowbytes * 4) / 3;
        }
        png_set_bgr (png);
        *width = png_get_image_width (png, info);
        *height = png_get_image_height (png, info);
        size = *height * *rowbytes;
        clipRowbytes = *rowbytes/32;
        if (*rowbytes % 32)
                ++clipRowbytes;
        clipSize = clipRowbytes * *height;
        // This gets freed by XDestroyImage
        *data = (unsigned char*) malloc (sizeof (png_byte) * size);
        rowPointers = (unsigned char**) malloc (*height * sizeof (unsigned char*));
        png_bytep cursor = *data;
    int i=0,x=0,y=0;
        for (i=0; i<*height; ++i, cursor += *rowbytes)
                rowPointers[i] = cursor;
        png_read_image (png, rowPointers);
        *clipData = (char*) calloc (clipSize, sizeof(unsigned char));
        if (colortype == PNG_COLOR_TYPE_RGB) {
                memset (*clipData, 0xff, clipSize);
        } else {
                // Set up bitmask for clipping fully transparent areas
                for (y=0; y<*height; ++y, cursor+=*rowbytes) {
                        for (x=0; x<*rowbytes; x+=4) {
                                // Set bit in mask when alpha channel is nonzero
                                if(rowPointers[y][x+3])
                                        (*clipData)[(y*clipRowbytes) + (x/32)] |= (1 << ((x/4)%8));
                        }
                }
        }
        TeardownPng (png, info);
    free (rowPointers);
}

void Xwindow::putImage(int x, int y, const char* filename) {
	XEvent ev;
	XNextEvent(d, &ev);
	cout << "OPEN FILE" << endl;
	FILE *file = fopen(filename, "r");
	cout << "SUCCESS" << endl;
	unsigned width_ = 0, height_ = 0;
	unsigned char *data = NULL;
	char *clip = NULL;
	unsigned rowbytes = 0;

	LoadPng(file, &data, &clip, &width_, &height_, &rowbytes);
        if (!data)
        	 return;
	XImage *ximage = XCreateImage (d, DefaultVisual(d, s), DefaultDepth(d,s), ZPixmap, 0, (char*)data, width_, height_, 8, rowbytes);

	if (ximage) {
                XPutImage (d, w, gc, ximage, 0, 0, 0, 0, width_, height_);
				cout << "put image" << endl;
				XFlush(d);
		} else {
                free (data);
        }
	cout << "WHILE ENDS" << endl;
	free (clip);
	cout << "FREE ENDS" << endl;
	XFlush(d);
	cout << "REACH END" << endl;
	// png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	// if(!png) abort();
	// cout << "NOT PNG ABORT" << endl;
	// png_infop info = png_create_info_struct(png);
	// if(!info) abort();
	// cout << "NOT INFO ABORT" << endl;
	// if(setjmp(png_jmpbuf(png))) abort();
	// png_init_io(png, file);
	// png_read_info(png, info);
	// cout << "ABORT1" << endl;
	// int width = 0, 
	// 	height = 0, 
	// 	colortype = 0, 
	// 	depth = 0,
	// 	interlace = 0,
	// 	compression = 0,
	// 	filter = 0;
	// unsigned rowbytes = 0;
	// size_t size = 0;
	// unsigned char *data = NULL;
	// png_bytep *rowPointers = NULL;
	// cout << "ABORT2" << endl;
	// png_get_IHDR(png, info, (png_uint_32*)width, (png_uint_32*)height, &depth, &colortype, &interlace, &compression, &filter);
	// cout << "ABORT3" << endl;
	// width = png_get_image_width(png, info);
  	// height = png_get_image_height(png, info);
  	// colortype = png_get_color_type(png, info);
  	// depth  = png_get_bit_depth(png, info);
	// rowbytes = png_get_rowbytes(png, info);
	// cout << "ABORT4" << endl;
	// size = height * rowbytes;
	// // clipRowByte = rowbytes/32;
	// // if (rowbytes % 32) ++clipRowByte;
	// // clipSize = clipRowbyte * height;

	// data = (unsigned char*)malloc(sizeof (png_byte) * size);
	// rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  	// for(int i = 0; i < height; i++) {
	// 	rowPointers[i] = (png_byte*)malloc(rowbytes);
	// }
	// png_read_image(png, rowPointers);
	// cout << "ABORT5" << endl;
	// //*clipData = (char*) calloc (clipSize, sizeof(unsigned char));
	// // if (colortype == PNG_COLOR_TYPE_RGB) {
	// // 	memset (*clipData, 0xff, clipSize);
	// // } else {
	// // 	// Set up bitmask for clipping fully transparent areas
	// // 	for (i = 0; i < height; ++ i, cursor+=*rowbytes) {
	// // 			for (x=0; x<*rowbytes; x+=4) {
	// // 					// Set bit in mask when alpha channel is nonzero
	// // 					if(rowPointers[y][x+3])
	// // 							(*clipData)[(y*clipRowbytes) + (x/32)] |= (1 << ((x/4)%8));
	// // 			}
	// // 	}
	// // }
	// fclose(file);
	// png_destroy_read_struct(&png, &info, NULL);
	// free(rowPointers);
	// cout << "ABORT6" << endl;
	// XImage *ximage = XCreateImage(d, DefaultVisual(d,s), DefaultDepth(d,s), ZPixmap, 0, (char*) data, width, height, 8, rowbytes);
	// cout << "ABORT7" << endl;
	// XPutImage(d, w, DefaultGC(d, s), ximage, 0, 0, 0, 0, width, height);
	// cout << "ABORT8" << endl;
	// XFlush(d);
}


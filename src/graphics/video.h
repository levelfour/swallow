#ifndef __VIDEO_H
#define __VIDEO_H

#define VRAM_TEXTMODE	0x000B8000
#define COLOR_BLACK			0x00
#define COLOR_BLUE			0x01
#define COLOR_GREEN			0x02
#define COLOR_CYAN			0x03
#define COLOR_RED			0x04
#define COLOR_MAGENTA		0x05
#define COLOR_BROWN			0x06
#define COLOR_LIGHT_GRAY	0x07
#define COLOR_DARK_GRAY		0x08
#define COLOR_LIGHT_BLUE	0x09
#define COLOR_LIGHT_GREEN	0x0A
#define COLOR_LIGHT_CYAN	0x0B
#define COLOR_LIGHT_RED		0x0C
#define COLOR_LIGHT_MAGENTA	0x0D
#define COLOR_LIGHT_BROWN	0x0E
#define COLOR_WHITE			0x0F
#define MAX_Y			25
#define MAX_X			80
#define	MAX_XY			(80*25)

#define CURSOR_DEFAULT		-1

typedef struct {
	int x;
	int y;
	int fc;		// foreground color
	int bc;		// background color
} CURSOR;

extern CURSOR _cursor;

void print(char c, unsigned char foreColor, unsigned char backColor, int x, int y);
void printchar(const char c);
void printstr(const char *str);
void init_screen();
void clear();
void set_cursor(int x, int y, int fc, int bc);

#endif // __VIDEO_H

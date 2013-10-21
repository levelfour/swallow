#include "video.h"
#include "string.h"
#include "asm_func.h"

CURSOR _cursor;

void print(	char c,
			unsigned char  foreColor,
			unsigned char backColor,
			int x,
			int y) {
	unsigned short  *vram_TextMode;
	unsigned short  color;

	vram_TextMode	= (unsigned short *)VRAM_TEXTMODE;
	color			= (backColor << 4) | (foreColor & 0x0F);
	vram_TextMode	+= x + y * MAX_X;
	*vram_TextMode	= (color << 8) | c;
}

void printchar(const char c) {
	switch(c) {
		case '\n':
			_cursor.x = 0;
			_cursor.y++;
			break;
		case '\016':
			print(' ', _cursor.fc, _cursor.bc, --_cursor.x, _cursor.y);
			break;
		case '\0':
			break;
		default:
			print(c, _cursor.fc, _cursor.bc, _cursor.x++, _cursor.y);
	}
}

void printstr(const char *str) {
	int i;
	for(i = 0; i < strlen(str); i++) {
		printchar(str[i]);
	}
}

void init_screen() {
	set_cursor(0, 0, COLOR_WHITE, COLOR_BLACK);
	clear();
	int i;
	for(i = 0; i < MAX_XY; i++) {
		printchar(' ');
	}
	set_cursor(0, 0, COLOR_WHITE, COLOR_BLACK);
}

void clear() {
	int x, y;
	for(y = 0; y < MAX_Y; y++) {
		for(x = 0; x < MAX_X; x++) {
			print(' ', COLOR_BLACK, COLOR_BLACK, x, y);
		}
	}
}

void set_cursor(int x, int y, int fc, int bc) {
	if(x >= 0) _cursor.x = x;
	if(y >= 0) _cursor.y = y;
	if(fc >= 0) _cursor.fc = fc;
	if(bc >= 0) _cursor.bc = bc;
}

void refresh() {
	int cursor_position = _cursor.y * MAX_X + _cursor.x;
	outb(0x3d4, 15);
	outb(0x3d5, cursor_position);
	outb(0x3d4, 14);
	outb(0x3d5, cursor_position >> 8);
}

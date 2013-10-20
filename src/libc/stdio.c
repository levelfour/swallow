#include "stdio.h"
#include "stdlib.h"
#include "video.h"
#include "types.h"

int sprintf(char *str, const char *format, ...) {
	char *dst = str;
	char const *src = format;
	bool isfmt = false;
	void *args = (&format + 1);
	int argn = 0;
	do {
		if(!isfmt && *src != '%') {
			*dst++ = *src;
		} else if(isfmt) {
			switch(*src) {
				case 'c':
					*dst++ = ((char*)args)[argn++];
					break;
				case 's':
					strcpy(dst, ((char**)args)[argn]);
					dst += strlen(((char**)args)[argn]);
					break;
				case 'd':
					dst += strlen(itoa(((int*)args)[argn++], dst, 10));
					break;
				case 'u':
					dst += strlen(utoa(((uint*)args)[argn++], dst, 10));
					break;
				case 'o':
					dst += strlen(utoa(((uint*)args)[argn++], dst, 8));
					break;
				case 'x':
				case 'p':
					dst += strlen(utoa(((uint*)args)[argn++], dst, 16));
					break;
				case '%':
					*dst++ = '%';
					break;
				default:
					return -1;
			}
			isfmt = false;
		} else if(*src == '%') {
			isfmt = true;
		}
	} while(*src++);
	return (int)strlen(str);
}

int printf(const char *format, ...) {
	char const *p = format;
	char buf[20];
	void *args = (&format + 1);
	int argn = 0;
	bool isfmt = false;
	int len = 0;
	
	do {
		if(*p == '\0') break;
		if(!isfmt && *p != '%') {
			printchar(*p);
			len++;
		} else if(isfmt) {
			switch(*p) {
				case 'c':
					printchar(((char*)args)[argn++]);
					len++;
					break;
				case 's':
					printstr(((char**)args)[argn]);
					len += (int)strlen(((char**)args)[argn++]);
					break;
				case 'd':
					len += (int)strlen(itoa(((int*)args)[argn++], buf, 10));
					printstr(buf);
					break;
				case 'u':
					len += (int)strlen(utoa(((uint*)args)[argn++], buf, 10));
					printstr(buf);
					break;
				case 'o':
					len += (int)strlen(utoa(((uint*)args)[argn++], buf, 8));
					printstr(buf);
					break;
				case 'x':
				case 'p':
					len += (int)strlen(utoa(((uint*)args)[argn++], buf, 16));
					printstr(buf);
					break;
				case '%':
					printchar('%');
					len++;
					break;
				default:
					return -1;
			}
			isfmt = false;
		} else if(*p == '%') {
			isfmt = true;
		}
	} while(*p++);

	return len;
}

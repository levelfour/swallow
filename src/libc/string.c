#include "string.h"

uint strlen(const char *str) {
	int len = 0;
	while(*str++) len++;
	return len;
}

char *strcpy(char *str1, const char *str2) {
	char *ret = str1;
	do {
		*str1++ = *str2++;
	} while(*str2);
	return ret;
}

void memset(void *s, unsigned char c, int size) {
	unsigned char *p	= (unsigned char *)s;
	while(size--) *p++ = c;
}

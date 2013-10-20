#include "stdlib.h"
#include "types.h"

char *itoa(int val, char *str, int radix) {
	const char number[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ret = str;

	if(val < 0) {
		*str++ = '-';
		val = -val;
	}

	int figure = 1, c = val;
	while(c /= radix) figure++;

	int i;
	str[figure] = '\0';
	c = val;
	for(i = 0; i < figure; i++) {
		str[figure-i-1] = number[c % radix];
		c /= radix;
	}

	return ret;
}

char *utoa(uint val, char *str, int radix) {
	const char number[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ret = str;

	int figure = 1;
	uint c = val;
	while(c /= radix) figure++;

	int i;
	str[figure] = '\0';
	c = val;
	for(i = 0; i < figure; i++) {
		str[figure-i-1] = number[c % radix];
		c /= radix;
	}

	return ret;
}

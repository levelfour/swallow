#ifndef __STDLIB_H
#define __STDLIB_H

#include "types.h"

#define NULL	0x0

char *itoa(int val, char *str, int radix);
char *utoa(uint val, char *str, int radix); 

#endif // __STDLIB_H

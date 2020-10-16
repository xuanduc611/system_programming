#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#define SPACE_CHAR      0x20

/**
 * @brief Count total occurrences of character in string.
 * @param string: The input string.
 * @param c: The character needed to be counted.
 * @return number of c in string.
*/
int ml_char_cnt(const char *string, char c);

#endif // _MY_LIB_H_

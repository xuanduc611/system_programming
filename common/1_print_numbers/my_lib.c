#include "my_lib.h"

int ml_char_cnt(const char *string, char c)
{
    int ret = 0;
    int i, len;

    len = strlen(string);

    for (i = 0; i < len; i++) {
        if (string[i] == SPACE_CHAR) {
            ret++;
        }
    }

    return ret;
}

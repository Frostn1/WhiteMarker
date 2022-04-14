#include "../inc/Character.h"

Word _Word(char val, int x, int y) {
    Word raw;
    raw.val = val;
    raw.pos = (x << 16) + (y);
    return raw;
}


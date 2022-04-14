#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>

typedef struct _word {
    char val; // Char value the word holds
    int pos; // Splits into two parts, with using bitshifts to reveal each part, first part is x cordinate and second part is y cordinate
    // x part -> ((x << 16) + (y)) >> 16
    // y part -> ((x << 16) + (y)) & 0x0000ffff
    // pos connection of x and y -> (x << 16) + (y)
}Word;

Word _Word(char val, int x, int y);

#endif // !CHARACTER_H
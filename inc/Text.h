#ifndef TEXT_H
#define TEXT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Character.h"
#include "Tool.h"

typedef struct _text {
    Word* string;
    int len;
    // Format _format; // Format for the entire text

    char* _rep;
}Text;

Text* _Text(char* str);
char* ToString(Text raw);


#endif // !TEXT_H
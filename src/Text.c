#include "../inc/Text.h"

Text* _Text(char* str) {
    
    // Init Normal Fields
    Text* raw = (Text*)malloc(sizeof(Text));
    raw->len = strlen(str);
    raw->_rep = strdup(str);
    raw->string = (Word*)malloc(sizeof(Word)*raw->len);


    int tempx = 1, tempy = 1, wp = 0; // wp -> wordPointer
    // Init String Field With `Word` Type
    for (size_t p = 0; p < raw->len; p++) {
        if(isSpace(raw->_rep[p])) {
            switch (raw->_rep[p]) {
            case TAB_ASCII:
                tempx += 3;
                break;
            case NEWLINE_ASCII:
                tempx = 0;
                tempy += 1;
                break;
            case CARRIAGERETURN_ASCII:
                tempx = 0;
                break;
            case SPACE_ASCII:
            default:
                break;
            }
        } else {
            *raw->string = _Word(raw->_rep[p],tempx, tempy);
        }

        tempx += 1;
    }
    

}

char* ToString(Text raw) {
    return raw._rep;
}
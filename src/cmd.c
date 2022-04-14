#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <wchar.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "../inc/Log.h"
#include "../inc/Character.h"
#include "../inc/Text.h"


#define ITALIC 3
#define UNDERLINE 4
#define FLASHING 5
#define INVERTED 7
#define STRIKE_THROUGH 9
#define DOUBLE_UNDERLINE 21
#define DARK_GRAY 30
#define RED 31
#define LIGHT_GREEN 32
#define YELLOW 33
#define BLUE 34
#define LIGHT_PURPLE 35
#define LIGHT_BLUE 36
#define WHITE 37
#define DEFAULT 39


void c(int color) {
	printf("\033[%dm", color);
}
int setupScreen() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }

    return -1;
}
void clearScreen() {
    printf("\e[1;1H\e[2J");
}

// 1 for show, 0 for hide
void cursorState(bool state) {
    state ? printf("\033[?25h") : printf("\033[?25l");
}
int rotatingRod() {
    

    int i, j, ms = 250;    
    const char *a = "|/-\\";
    time_t start, now;
    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = ms * 1000000L;
    cursorState(false);  // hide the cursor
    time(&start);
    while(1) {
        for (i = 0; i < 4; i++) {
            // printf("\1xb[2J");          // clear terminal
            clearScreen();
            printf("\033[0;0H");        // place cursor at top left corner
            for (j = 0; j < 80; j++) {  // 80 character terminal width, say
                printf("%c", a[i]);
            }
            fflush(stdout);
            //nanosleep(&delay, NULL);
        }
        // stop after 20 seconds, say
        time(&now);
        if (difftime(now, start) >= 20) break;
    }
    cursorState(true); // restore the cursor
    
}
void cursorVoodoo() {
    // printf("\033[1;32mHello the\v\are");
    clearScreen();
    // printf("\e[H HEllo there \e[H What");
    // Save pos

    printf("Hello world");
    printf("\e7");
    printf("Hello world");
    printf("\e8");
    printf("What");
}

void printColorTable() {
    for (size_t i = 0; i < 256; i++) {
        printf("\e[38;5;%dm",i);
        printf("%d ", i);
    }
}

void rgb(int R, int G, int B) {
    printf("\e[38;2;%d;%d;%dm",R,G,B);
}

void moveCursor(int x, int y) {
    printf("\033[%d;%dH",x,y);  
}

// moves cursor left n columns
void moveColumnsLeft(int n) {
    printf("\e[%dD",n);
}

// moves cursor right n columns
void moveColumnsRight(int n) {
    printf("\e[%dC",n);
}

// moves cursor down n lines
void moveLinesDown(int n) {
    printf("\e[%dB", n);
}

// moves cursor up n lines
void moveLinesUp(int n) {
    printf("\e[%dA", n);
}

// moves cursor to beginning of next line, n lines down
void moveToStartNextLine(int n) {
    printf("\e[%dE",n);
}

void savePos() {
    printf("\e7");
}

void movePos() {
    printf("\e8");
}

void animateABC() {
    const char* text = "Hello world";
    const int length = strlen(text), ms = 300;
    time_t start, now;
    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 4500000000L;
    cursorState(false);  // hide the cursor
    
    clearScreen();
    // place cursor at top left corner
    moveCursor(0,0);
    const int baseColor = 50, intenseColor = 255;
    bool writeFlag = true;
    rgb(0,0,baseColor);
    printf("%s",text);
    while(1) {
        moveCursor(0,0);
        for (size_t i = 0; i < length; i++) {
            if(isSpace(text[i])) {
                // printf("Info : %d\n", text[i]);
                // getchar();

                // switch(text[i]) {
                //     case ' ':
                //     case '\t':
                //     moveColumnsRight(1);
                //     break;
                //     printf("DONT GO HERE !!\n");
                //     case '\n':
                //     moveToStartNextLine(1);
                //     break;

                //     default:
                //     break;
                // }
                continue;
                writeFlag = false;
                // writeLog("Got here %d\n");
                // writeLog("Not here\n");
            } else {
                rgb(0,0,intenseColor);
                writeFlag ? putchar(text[i]) : writeFlag;
                rgb(0,0,intenseColor / 2);
                
                if(i != length - 1) {
                    writeFlag ? putchar(text[i + 1]) : writeFlag;
                    moveColumnsLeft(1);
                }
                if(i) {
                    moveColumnsLeft(2);
                    writeFlag ? putchar(text[i - 1]) : writeFlag;
                    moveColumnsRight(1);
                }

                nanosleep(&delay, NULL);
                // Sleep(&delay);
                if(i) {
                    moveColumnsLeft(2);
                    rgb(0,0,baseColor);
                    writeFlag ? putchar(text[i - 1]) : writeFlag;
                    moveColumnsRight(1);
                }
                moveColumnsLeft(1);
                writeFlag ? putchar(text[i]) : writeFlag;
            }
            
       
        }
    }
    
    cursorState(true); // restore the cursor
}

void printArray(int* array, int size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ",array[i]);
    }
    putchar('\n');
    
}
int main () {
    if(setupScreen() != -1 ) return 1;
    cursorState(true);
    _Log("debug.log");
    printColorTable();
    animateABC();
    // Word wrd = _Word('A', 2755, 3888);
    
    

    LogF();
    c(DEFAULT);
    getchar();
    return 0; 
}


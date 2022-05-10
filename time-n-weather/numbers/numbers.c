#include <ncurses.h>

#include "numbers.h"

#define NUMBER_WIDTH 5
#define NUMBER_HEIGHT 5

void writeZero(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = NUMBER_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i, j;
    
    move(yp, xp);

    addch(ACS_ULCORNER);
    for ( i = 0; i < width; i++ ) {
       xp++;
       move(yp, xp);
       addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    for ( j = 0; j < height; j++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        for ( i = 0; i < width; i++ ) {
            xp++;
        }
        xp++;
        move(yp, xp);
        addch(ACS_VLINE);
    
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeOne(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeTwo(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeThree(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_RTEE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeFour(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_TTEE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_TTEE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_PLUS);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeFive(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeSix(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LTEE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeSeven(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeEight(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LTEE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_RTEE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeNine(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_VLINE);
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_RTEE);

    xp = x;
    yp++;
    xp++;
    xp++;
    xp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_HLINE);
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

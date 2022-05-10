#include <ncurses.h>

#include "numbers.h"

// height should be odd number like 5 7 for numbers like 2 and 3
#define NUMBER_WIDTH 5
#define NUMBER_HEIGHT 5

void writeZero(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = NUMBER_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;
    
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

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
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

    int width = NUMBER_WIDTH - 2;
    int height = NUMBER_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    xp += width;
    move(yp, xp);
    addch(ACS_URCORNER);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        xp += width;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    xp += width;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeTwo(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

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

    
    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_ULCORNER);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);

    xp = x;
    for ( i = 0; i < height; i++ ) {
        yp++;
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

void writeThree(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2;

    int xp = x;
    int yp = y;

    int i;
    
    move(yp, xp);

    addch(ACS_HLINE);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    xp++;
    for ( i = 0; i < width - 1; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_RTEE);

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeFour(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_TTEE);
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_TTEE);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
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
    addch(ACS_PLUS);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeFive(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2; 
    
    int xp = x;
    int yp = y;
    
    int i;
    
    move(yp, xp);

    addch(ACS_ULCORNER);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    xp += width;
    xp++;
    for ( i =0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeSix(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_ULCORNER);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LTEE);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LLCORNER);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_LRCORNER);
}

void writeSeven(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = NUMBER_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;

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

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }

    xp = x;
    yp++;
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

void writeEight(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = (NUMBER_HEIGHT - 3) / 2;

    int xp = x;
    int yp = y;
    
    int i;

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

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_VLINE);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_LTEE);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_HLINE);
    }
    xp++;
    move(yp, xp);
    addch(ACS_RTEE);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
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

void writeNine(int x, int y) {

    int width = NUMBER_WIDTH - 2;
    int height = NUMBER_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;

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

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_VLINE);
        xp += width;
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
    addch(ACS_RTEE);

    
    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
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

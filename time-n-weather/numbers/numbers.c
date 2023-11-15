#include <ncurses.h>

#include "numbers.h"

void writeZero(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = CLOCK_FONT_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;
    
    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
       xp++;
       move(yp, xp);
       addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeOne(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = CLOCK_FONT_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    xp += width;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        xp += width;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    xp += width;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeTwo(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    
    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    xp = x;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);   
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeThree(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;

    int xp = x;
    int yp = y;

    int i;
    
    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    xp++;
    for ( i = 0; i < width - 1; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeFour(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeFive(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2; 
    
    int xp = x;
    int yp = y;
    
    int i;
    
    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    xp = x;
    xp += width;
    xp++;
    for ( i =0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeSix(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;
    
    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i =0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i =0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeSeven(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = CLOCK_FONT_HEIGHT - 2;

    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }

    xp = x;
    yp++;
    xp += width;
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeEight(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;

    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

void writeNine(int x, int y) {

    int width = CLOCK_FONT_WIDTH - 2;
    int height = (CLOCK_FONT_HEIGHT - 3) / 2;

    int xp = x;
    int yp = y;
    
    int i;

    move(yp, xp);

    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    for ( i = 0; i < height; i++ ) {
        xp = x;
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
        xp += width;
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }

    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);

    
    xp = x;
    xp += width;
    xp++;
    for ( i = 0; i < height; i++ ) {
        yp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    
    xp = x;
    yp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
    for ( i = 0; i < width; i++ ) {
        xp++;
        move(yp, xp);
        addch(ACS_CKBOARD);
    }
    xp++;
    move(yp, xp);
    addch(ACS_CKBOARD);
}

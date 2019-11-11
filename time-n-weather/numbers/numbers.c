#include <ncurses.h>

#include "numbers.h"

void writeZero(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    addch(ACS_ULCORNER);
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
     addch(ACS_LRCORNER);
}

void writeOne(int x, int y) {

    int xp = x;
    int yp = y;

    move(yp, xp);

    xp++;
    move(yp, xp);
    addch(ACS_URCORNER);

    xp = x;
    yp++;
    xp++;
    move(yp, xp);
    addch(ACS_VLINE);

    xp = x;
    yp++;
    xp++;
    move(yp, xp);
    addch(ACS_BTEE);
}

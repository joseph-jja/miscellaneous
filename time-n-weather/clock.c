#include <ncurses.h>

#include <string.h>

#include <time.h>
#include <unistd.h>

#include "numbers/numbers.h"

static char *days[7];
static char *months[12];

void setupDays() {
   
    days[0] = "Sunday";
    days[1] = "Monday";
    days[2] = "Tuesday";
    days[3] = "Wednesday";
    days[4] = "Thursday";
    days[5] = "Friday";
    days[6] = "Saturday";
}

void setupMonths() {
    months[0] = "January";
    months[1] = "February";
    months[2] = "March";
    months[3] = "April";
    months[4] = "May";
    months[5] = "June";
    months[6] = "July";
    months[7] = "August";
    months[8] = "September";
    months[9] = "October";
    months[10] = "November";
    months[11] = "December";
}

void writeNumber(int x, int y, int num) {

    switch(num) {
        case 0: 
             writeZero(x, y);
            break;
        case 1: 
             writeOne(x, y);
            break;
        case 2: 
             writeTwo(x, y);
            break;
        case 3: 
             writeThree(x, y);
            break;
        case 4: 
             writeFour(x, y);
            break;
        case 5: 
             writeFive(x, y);
            break;
        case 6: 
             writeSix(x, y);
            break;
        case 7: 
             writeSeven(x, y);
            break;
        case 8: 
             writeEight(x, y);
            break;
        case 9: 
             writeNine(x, y);
            break;
        default: 
            break;
    }
}

char *get_time() {

    time_t now = time(NULL);
    const struct tm *localNow = localtime(&now);

    int year = 1900 + localNow->tm_year;
    int month = localNow->tm_mon;

    char ampm[3];

    memset(ampm, '\0', sizeof(ampm));

    int imin = localNow->tm_min;
    int ihours = localNow->tm_hour;
    if (ihours > 12) {
        ihours -=12;
        sprintf(ampm, "%s", "PM");
    } else {
        sprintf(ampm, "%s", "AM");
    }

    move(1, 2);
    printw("%s, %s %d, %d", days[localNow->tm_wday], months[month], localNow->tm_mday, year);

    if (ihours < 10) {
        writeNumber(4, 4, 0);
        writeNumber(8, 4, ihours);
    } else {
        writeNumber(4, 4, 1);
        writeNumber(8, 4, ihours - 10);
    }

    move(5, 13);
    addch(ACS_BULLET);
    move(6, 13);
    addch(ACS_BULLET);

    if (imin < 10) {
        writeNumber(15, 4, 0);
        writeNumber(19, 4, imin);
    } else {
        int x = imin / 10;
        writeNumber(15, 4, x);
        writeNumber(19, 4, imin - (x * 10));
    }

    move(6, 23);
    printw("%s", ampm);

    return asctime(localNow);
}

int main()
{	
        setupDays();
        setupMonths();
	initscr();	
        //attron(A_BOLD);
        //attron(A_STANDOUT);
        while (1) {
            //int y, x;
            //getyx(stdscr, y, x);
            /*if (has_colors() == TRUE) {
                start_color();	
	        init_pair(1, COLOR_RED, COLOR_BLACK);
                attron(COLOR_PAIR(1));
            }*/
	    //printw("Time %s", get_time());	
	    get_time();
            /*if (has_colors() == TRUE) {
                attroff(COLOR_PAIR(1));
            }*/
	    refresh();		
            sleep(1);
        }
	//getch();			/* Wait for user input */
	endwin();		

	return 0;
}

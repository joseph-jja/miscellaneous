#include <ncurses.h>

#include <time.h>
#include <unistd.h>

static char *days[7];

void setupDays() {
   
    days[0] = "Sunday";
    days[1] = "Monday";
    days[2] = "Tuesday";
    days[3] = "Wednesday";
    days[4] = "Thursday";
    days[5] = "Friday";
    days[6] = "Saturday";
}

char *get_time() {

    time_t now = time(NULL);
    const struct tm *localNow = localtime(&now);

    int year = 1900 + localNow->tm_year;
    int month = 1 + localNow->tm_mon;

    move(0, 0);
    printw("%d %d %d", year, month, localNow->tm_mday);
    move(2, 2);
    printw("%d %d %s", localNow->tm_hour, localNow->tm_min, days[localNow->tm_wday]);

    return asctime(localNow);
}

int main()
{	
        setupDays();
	initscr();			
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

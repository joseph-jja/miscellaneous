#include <ncurses.h>

#include <string.h>

#include <time.h>
#include <unistd.h>

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

char *get_time() {

    time_t now = time(NULL);
    const struct tm *localNow = localtime(&now);

    int year = 1900 + localNow->tm_year;
    int month = localNow->tm_mon;

    char hours[3], 
        ampm[3];

    memset(hours, '\0', sizeof(hours));
    memset(ampm, '\0', sizeof(ampm));

    int ihours = localNow->tm_hour;
    if (ihours > 12) {
        ihours -=12;
        sprintf(ampm, "%s", "PM");
    } else {
        sprintf(ampm, "%s", "AM");
    }

    if (ihours < 10) {
        sprintf(hours, "0%d", ihours);
    } else {
        sprintf(hours, "%d", ihours);
    } 

    move(0, 0);
    printw("%s, %s %d, %d", days[localNow->tm_wday], months[month], localNow->tm_mday, year);
    move(2, 0);
    printw("%s:%d %s", hours, localNow->tm_min, ampm);

    return asctime(localNow);
}

int main()
{	
        setupDays();
        setupMonths();
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

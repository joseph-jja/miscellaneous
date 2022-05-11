#include <ncurses.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>

#include "numbers/numbers.h"
#include "whichnodejs.h"

#define WEATHER_MAP "/weather-api.js"
#define WEATHER_MAP_LEN strlen(WEATHER_MAP)
#define OPEN_WEATHER_MAP "/ow-weather-api.js"
#define OPEN_WEATHER_MAP_LEN strlen(OPEN_WEATHER_MAP)

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

char *get_nodejs_path() {

    if (getenv("CLOCK_NODEJS_BIN")) {
        printf("Try setting CLOCK_NODEJS_BIN if node.js is not in your path\n");
        sleep(5);
        return getenv("CLOCK_NODEJS_BIN");
    } else {
        return NODE_JS;
    }
}

char *get_weather_api() {

    char *pwd = getenv("PWD");
    int wsize = strlen(pwd) + WEATHER_MAP_LEN + 1;
    char *weather = malloc(wsize);
    memset(weather, '\0', wsize);
    sprintf(weather, "%s%s", pwd, WEATHER_MAP);
    return weather;
}

char *get_ow_weather_api() {
    char *pwd = getenv("PWD");
    int wsize = strlen(pwd) + OPEN_WEATHER_MAP_LEN + 1;
    char *weather = malloc(wsize);
    memset(weather, '\0', wsize);
    sprintf(weather, "%s%s", pwd, OPEN_WEATHER_MAP);
    return weather;
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
        writeNumber(4, 2, 0);
        writeNumber(10, 2, ihours);
    } else {
        writeNumber(4, 2, 1);
        writeNumber(10, 2, ihours - 10);
    }

    move(3, 16);
    addch(ACS_CKBOARD);
    move(5, 16);
    addch(ACS_CKBOARD);

    if (imin < 10) {
        writeNumber(18, 2, 0);
        writeNumber(24, 2, imin);
    } else {
        int x = imin / 10;
        writeNumber(18, 2, x);
        writeNumber(24, 2, imin - (x * 10));
    }

    move(4, 29);
    printw("%s", ampm);

    return asctime(localNow);
}

long stat_file(char *filename) {

    struct stat sb;

    if (stat(filename, &sb) == -1) {
        return 0;
    }
    return (long long) sb.st_size;
}

void read_in_file(char *filename, long x, long y) {

     long readSize = stat_file(filename) + 1;
     if (readSize <= 0) {
        return;
     }

     FILE *pFile;

     long posy = y;
     if ((pFile = fopen(filename, "r")) != NULL) {
         char *buffer = (char *)malloc(readSize);
         if (buffer == NULL) {
             return;
         }
         memset(buffer, '\0', readSize);
         while (fgets(buffer, readSize -1, pFile) != NULL) {
             move(posy, x);
             printw("%s", buffer);
             memset(buffer, '\0', readSize);
             posy++;
         }
         free(buffer);

         fclose(pFile);
     }
}

int main()
{
        setupDays();
        setupMonths();

        char *weather = get_weather_api();
        char *owweather = get_ow_weather_api();
        char *nodejsBin = get_nodejs_path();

        // child process for weather map
        pid_t wpID = fork();
        char *wmap[] = { nodejsBin, weather, NULL};
        if ( wpID == 0 ) {
            execvp(wmap[0], wmap);
            exit(0);
        }

        // child process for open weather map
        pid_t pID = fork();
        char *owmap[] = { nodejsBin, owweather, NULL};
        if ( pID == 0 ) {
            execvp(owmap[0], owmap);
            exit(0);
        }

	initscr();
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        attron(A_BOLD);
        int i = 0;
        if (has_colors() == TRUE) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_WHITE, COLOR_BLACK);
            init_pair(3, COLOR_CYAN, COLOR_BLACK);
            init_pair(4, COLOR_YELLOW, COLOR_BLACK);
            init_pair(5, COLOR_GREEN, COLOR_BLACK);
            init_pair(6, COLOR_BLUE, COLOR_BLACK);
        }
        while (1) {
            if (has_colors() == TRUE) {
                if ( i == 0 ) {
                    attron(COLOR_PAIR(1));
                } else if ( i == 1 ) {
                    attron(COLOR_PAIR(2));
                } else if ( i == 2 ) {
                    attron(COLOR_PAIR(3));
                } else if ( i == 3 ) {
                    attron(COLOR_PAIR(4));
                } else if ( i == 4 ) {
                    attron(COLOR_PAIR(5));
                } else if ( i == 5 ) {
                    attron(COLOR_PAIR(6));
                } else {
                    i = 0;
                    attron(COLOR_PAIR(1));
                }
            }
            clear();
	    get_time();
            read_in_file("/tmp/details.txt", 5, 30);
            read_in_file("/tmp/hourly.txt", 12, 30);
	    refresh();
            sleep(1);
            i++;
        }
	//getch();			/* Wait for user input */
	endwin();

	return 0;
}

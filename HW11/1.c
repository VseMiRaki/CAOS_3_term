#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int year;
    int mon;
    int day;
    int hour;
    int minute;
    scanf("%4d-%2d-%2d %2d:%2d", &year, &mon, &day, &hour, &minute);
    struct tm old;
    memset(&old, 0, sizeof(old));
    old.tm_year = year - 1900;
    old.tm_mon = mon - 1;
    old.tm_mday = day;
    old.tm_isdst = -1;
    old.tm_hour = hour;
    old.tm_min = minute;
    struct tm new;
    while (scanf("%4d-%2d-%2d %2d:%2d", &year, &mon, &day, &hour, &minute) != EOF) {
        memset(&new, 0, sizeof(new));
        new.tm_year = year - 1900;
        new.tm_mon = mon - 1;
        new.tm_mday = day;
        new.tm_isdst = -1;
        new.tm_hour = hour;
        new.tm_min = minute;
        int new_time = mktime(&new);
        int old_time = mktime(&old);
        int time_segment = new_time - old_time;
        time_segment /= 60;
        printf("%d \n", time_segment);
        old = new;
    }
}
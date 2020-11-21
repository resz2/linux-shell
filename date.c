#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void local(void);
void utc(void);
void set(char *dString);
int dayofweek(int d, int m, int y);
char *dayS(int day);
char *monS(int month);

int main(int argc, char **argv) {
    if(argc==1) {
        local();
    }
    else if(argc==2)    {
        if(argv[1][0]!='-') {
            perror("invalid command, enter flags first");
            exit(EXIT_FAILURE);
        }
        if(argv[1][1]=='u')   {
            if(strlen(argv[1])==2)  utc();
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }
        }
        else    {
            if(argv[1][1]=='d') {
                perror("d flag requires 1 more argument");
                exit(EXIT_FAILURE);
            }
            else    {
                perror("option not supported");
                exit(EXIT_FAILURE);
            }
        }
    }
    else if(argc==3)    {
        if(strcmp(argv[1], "-u")==0 || strcmp(argv[2], "-u")==0)    {
            perror("u flag is a standalone flag");
            exit(EXIT_FAILURE);
        }
        if(argv[1][0]!='-') {
            perror("invalid command, enter flags first");
            exit(EXIT_FAILURE);
        }
        if(argv[1][1]=='d' && strlen(argv[1])==2)   {
            set(argv[2]);
        }
        else    {
            perror("option not supported");
            exit(EXIT_FAILURE);
        }
    }
    else    {
        perror("invalid command, max number of words should be 3");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void local(void)    {
    time_t cur;
    time(&cur);
    char *tString = ctime(&cur);
    for(int i=0;i<strlen(tString);i++)  {
        if(i==(strlen(tString)-5))  printf("IST ");
        printf("%c", tString[i]);
    }
}

void utc(void)  {
    time_t cur;
    struct tm *utime;
    time(&cur);
    utime = gmtime(&cur);
    time_t utctime = mktime(utime);
    char *tString = ctime(&utctime);

    for(int i=0;i<strlen(tString);i++)  {
        if(i==(strlen(tString)-5))  printf("UTC ");
        printf("%c", tString[i]);
    }
}

void set(char *dString) {
    int day, date, month, year;
    char *dS, *mS;
    sscanf(dString, "%d/%d/%d", &month, &date, &year);
    day = dayofweek(date, month, year);
    dS = dayS(day);
    mS = monS(month);
    printf("%s %s %d 00:00:00 IST %d\n", dS, mS, date, year);
}

int dayofweek(int d, int m, int y)  {
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

char *dayS(int day) {
    switch (day)    {
        case 1:
            return "Mon";
        case 2:
            return "Tue";
        case 3:
            return "Wed";
        case 4:
            return "Thu";
        case 5:
            return "Fri";
        case 6:
            return "Sat";
        case 7:
            return "Sun";
        default:
            perror("Invalid entry");
            exit(EXIT_FAILURE);
    }
}

char *monS(int month)   {
    switch (month)    {
        case 1:
            return "Jan";
        case 2:
            return "Feb";
        case 3:
            return "Mar";
        case 4:
            return "Apr";
        case 5:
            return "May";
        case 6:
            return "Jun";
        case 7:
            return "Jul";
        case 8:
            return "Aug";
        case 9:
            return "Sep";
        case 10:
            return "Oct";
        case 11:
            return "Nov";
        case 12:
            return "Dec";
        default:
            perror("Invalid entry");
            exit(EXIT_FAILURE);
    }
}
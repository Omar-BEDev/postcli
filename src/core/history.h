#ifndef HISTORY
#define HISTORY

//DATE FORMAT : "2026/12/30"
#define LAST_YEAR_INDEX_POSITION 3 
#define FIRST_MONTH_INDEX_POSITION 5
#define LAST_MONTH_INDEX_POSITION 6
#define FIRST_DAY_INDEX_POSITION 8
#define LAST_DAY_INDEX_POSITION 9
#define DATE_LENGTH 10

typedef struct Date{
    int year;
    int month;
    int day;
} Date;

Date str_to_date(char *date);
int is_date_bigger(char *current_date, char *date);   
int is_date_small(char *current_date, char *date);   
#endif
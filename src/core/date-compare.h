#ifndef DATE_COMPARE
#define DATE_COMPARE
#include "histroy/history.h"


typedef struct Date{
    int year;
    int month;
    int day;
} Date;


Date str_to_date(char *date);
int is_date_bigger(char *current_date, char *date);
int is_date_small(char *current_date, char *date);
#endif
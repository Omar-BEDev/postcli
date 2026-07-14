#ifndef DATE_COMPARE
#define DATE_COMPARE
#include "history/history.h"


typedef struct Date{
    int year;
    int month;
    int day;
} Date;


/**
 * @brief Converts a string to a Date structure
 * @param date The date string to convert
 * @return The Date structure
 */
Date str_to_date(char *date);
/**
 * @brief Checks if current_date is strictly greater than date
 * @param current_date The current date string
 * @param date The date string to compare against
 * @return 1 if current_date is bigger, 0 otherwise
 */
int is_date_bigger(char *current_date, char *date);
/**
 * @brief Checks if current_date is strictly smaller than date
 * @param current_date The current date string
 * @param date The date string to compare against
 * @return 1 if current_date is smaller, 0 otherwise
 */
int is_date_small(char *current_date, char *date);
#endif
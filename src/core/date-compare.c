#include "date-compare.h"

/**
 * @brief Converts a string to a Date structure
 * @param date The date string to convert
 * @return The Date structure
 */
Date str_to_date(char *date) {
  int year = 0;
  int month = 0;
  int day = 0;
  int i = 1;
  int year_length_value = 1000;
  year = (date[0] - 48) * year_length_value;
  while (i < DATE_LENGTH) {
    if (i <= LAST_YEAR_INDEX_POSITION) {
      year_length_value /= 10;
      year += (date[i] - 48) * (year_length_value);
    }
    if (i >= FIRST_MONTH_INDEX_POSITION && i <= LAST_MONTH_INDEX_POSITION) {
      if (i == LAST_MONTH_INDEX_POSITION) {
        month += date[i] - 48;
      }
      else {
      month += (date[i] - 48) * 10;
      }
    }
    if (i >= FIRST_DAY_INDEX_POSITION && i <= LAST_DAY_INDEX_POSITION) {
      if (i == LAST_DAY_INDEX_POSITION) {
        day += date[i] - 48;
      }
      else {
      day += (date[i] - 48) * 10;
      }
    }
    i++;
  }
  Date result = {year, month, day};
  return result;
}

/**
 * @brief Checks if current_date is strictly greater than date
 * @param current_date The current date string
 * @param date The date string to compare against
 * @return 1 if current_date is bigger, 0 otherwise
 */
int is_date_bigger(char *current_date, char *date) {
  Date first_date = str_to_date(current_date);
  Date second_date = str_to_date(date);

  if (first_date.year > second_date.year) {
    return 1;
  } else if (first_date.year == second_date.year &&
             first_date.month != second_date.month) {
    if (first_date.month > second_date.month) {
      return 1;
    }
  } else if (first_date.year == second_date.year &&
             first_date.month == second_date.month &&
             first_date.day != second_date.day) {
    if (first_date.day > second_date.day) {
      return 1;
    }
  }

  return 0;
}

/**
 * @brief Checks if current_date is strictly smaller than date
 * @param current_date The current date string
 * @param date The date string to compare against
 * @return 1 if current_date is smaller, 0 otherwise
 */
int is_date_small(char *current_date, char *date) {
  Date first_date = str_to_date(current_date);
  Date second_date = str_to_date(date);

  if (first_date.year < second_date.year) {
    return 1;
  } else if (first_date.year == second_date.year &&
             first_date.month != second_date.month) {
    if (first_date.month < second_date.month) {
      return 1;
    }
  } else if (first_date.year == second_date.year &&
             first_date.month == second_date.month &&
             first_date.day != second_date.day) {
    if (first_date.day < second_date.day) {
      return 1;
    }
  }

  return 0;
}

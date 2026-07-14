#include "../../utils/dynamic-array.h"
#include "../date-compare.h"
#include <stdlib.h>



/**
 * @brief Finds the first history index for a date
 * @param history_arr The history array
 * @param low The low index
 * @param high The high index
 * @param mid The middle index
 * @param date The date to find
 * @param indexes The index array
 * @param match The current match
 */
void first_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes, int match) 
{

  while (low <= high) {
    mid = (low + high) / 2;

    if (strcmp(history_arr->history[mid]->date, date) == 0) {
      indexes[0] = mid;
      match = mid;
      high = mid - 1;
    }
    if (is_date_bigger(history_arr->history[mid]->date, date) == 1) {
      high = mid - 1;
    }
    if (is_date_small(history_arr->history[mid]->date, date) == 1) {
      low = mid + 1;
      
    }
  }
  if (strcmp(history_arr->history[match]->date, date) != 0) {
    indexes[0] = -1;
  }
}

/**
 * @brief Finds the last history index for a date
 * @param history_arr The history array
 * @param low The low index
 * @param high The high index
 * @param mid The middle index
 * @param date The date to find
 * @param indexes The index array
 * @param match The current match
 */
void last_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes, int match) 
{
    low = 0;
    high = history_arr->length - 1;

    while(low <= high) {
        mid = (low + high) / 2;
        if (strcmp(history_arr->history[mid]->date, date) == 0) {
            indexes[1] = mid;
            match = mid;
            low = mid + 1;
        }
        if (is_date_bigger(history_arr->history[mid]->date, date) == 1) {
            high = mid - 1;
        }
        if (is_date_small(history_arr->history[mid]->date, date) == 1) {
            low = mid + 1;
        }
    }
    if (strcmp(history_arr->history[match]->date, date) != 0) {
      indexes[1] = -1;
    }
}
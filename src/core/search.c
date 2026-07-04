#include "../utils/dynamic-array.h"
#include "history.h"
#include <stdlib.h>

void first_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes) 
{

  while (low <= high) {
    mid = (low + high) / 2;

    if (strcmp(history_arr->history[mid]->date, date) == 0) {
      indexes[0] = mid;
      low = mid + 1;
    }
    if (is_date_bigger(history_arr->history[mid]->date, date) == 1) {
      low = mid + 1;
    }
    if (is_date_small(history_arr->history[mid]->date, date) == 1) {
      high = mid - 1;
      
    }
  }
  if (low > high) {
    indexes[0] = -1;
  }
}

void last_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes) 
{
    low = 0;
    high = history_arr->length - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if (strcmp(history_arr->history[mid]->date, date) == 0) {
            indexes[1] = mid;
            low = mid + 1;
        }
        if (is_date_bigger(history_arr->history[mid]->date, date) == 1) {
            low = mid + 1;
        }
        if (is_date_small(history_arr->history[mid]->date, date) == 1) {
            high = mid - 1;
        }
    }
    if (low > high) {
      indexes[1] = -1;
    }
}
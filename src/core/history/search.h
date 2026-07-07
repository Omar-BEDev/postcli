#ifndef SEARCH
#define SEARCH
#include "../../utils/dynamic-array.h"
void first_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes, int match);
void last_history_index(HistoryArray *history_arr, int low, 
                         int high, int mid,
                         char *date, int *indexes, int match);
#endif
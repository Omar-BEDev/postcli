#ifndef HISTORY
#define HISTORY
#include "../../utils/dynamic-array.h"
//DATE FORMAT : "2026/12/30"
#define LAST_YEAR_INDEX_POSITION 3 
#define FIRST_MONTH_INDEX_POSITION 5
#define LAST_MONTH_INDEX_POSITION 6
#define FIRST_DAY_INDEX_POSITION 8
#define LAST_DAY_INDEX_POSITION 9
#define DATE_LENGTH 10
/**
 * @brief Searches for history indexes for a given date
 * @param history_arr The history array
 * @param date The date to search
 * @param indexes The resulting indexes
 */
void search_history_indexes(HistoryArray *history_arr, char *date, int *indexes);
#endif
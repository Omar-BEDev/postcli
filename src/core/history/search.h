#ifndef SEARCH
#define SEARCH
#include "../../utils/dynamic-array.h"
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
                         char *date, int *indexes, int match);
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
                         char *date, int *indexes, int match);
#endif
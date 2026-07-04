#include "history.h"
#include "../../utils/dynamic-array.h"
#include "search.h"

void search_history_indexes(HistoryArray *history_arr, char *date, int *indexes) {
    int low = 0;
    int high = history_arr->length - 1;
    int mid = 0;
    first_history_index(history_arr, low, high, mid, date, indexes);
    last_history_index(history_arr, low, high, mid, date, indexes);
}



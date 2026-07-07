#include "history.h"
#include "../../utils/dynamic-array.h"
#include "search.h"
#include <stdio.h>

void search_history_indexes(HistoryArray *history_arr, char *date, int *indexes) {
    if (history_arr->length == 0) {
        printf("error: logs not found");
        return;
    }
    int low = 0;
    int high = history_arr->length - 1;
    int mid = 0;
    int match = 0;
    first_history_index(history_arr, low, high, mid, date, indexes, match);
    last_history_index(history_arr, low, high, mid, date, indexes, match);
}



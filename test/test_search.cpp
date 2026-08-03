#include "core/date-compare.h"
#include "core/history/history.h"
#include "core/history/search.h"
#include "utils/dynamic-array.h"
#include "crash_guard.h"
#include <gtest/gtest.h>
#include <cstdlib>

static void free_history(HistoryArray *arr) {
    for (int i = 0; i < arr->length; i++) {
        free(arr->history[i]->date);
        free(arr->history[i]->message);
        free(arr->history[i]);
    }
    free(arr->history);
    arr->history = nullptr;
    arr->length = 0;
}

static HistoryArray make_array(const char *const *dates, const char *const *msgs, int n) {
    HistoryArray arr = {};
    for (int i = 0; i < n; i++) {
        add_history_log(&arr, (char *)dates[i], (char *)msgs[i]);
    }
    return arr;
}

TEST(SearchHistoryIndexes, SingleMatch) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    search_history_indexes(&arr, (char *)"2026/01/02", indexes);
    EXPECT_EQ(indexes[0], 1);
    EXPECT_EQ(indexes[1], 1);
    free_history(&arr);
}

TEST(SearchHistoryIndexes, DuplicateDates) {
    const char *dates[] = {"2026/01/01", "2026/01/01", "2026/01/02"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    search_history_indexes(&arr, (char *)"2026/01/01", indexes);
    EXPECT_EQ(indexes[0], 0);
    EXPECT_EQ(indexes[1], 1);
    free_history(&arr);
}

TEST(SearchHistoryIndexes, AbsentDate) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    search_history_indexes(&arr, (char *)"2026/01/05", indexes);
    EXPECT_EQ(indexes[0], -1);
    EXPECT_EQ(indexes[1], -1);
    free_history(&arr);
}

TEST(SearchHistoryIndexes, SingleElement) {
    const char *dates[] = {"2026/01/01"};
    const char *msgs[] = {"a"};
    HistoryArray arr = make_array(dates, msgs, 1);
    int indexes[2] = {-1, -1};
    search_history_indexes(&arr, (char *)"2026/01/01", indexes);
    EXPECT_EQ(indexes[0], 0);
    EXPECT_EQ(indexes[1], 0);
    free_history(&arr);
}

TEST(SearchHistoryIndexes, EmptyArray) {
    HistoryArray arr = {};
    int indexes[2] = {-99, -99};
    search_history_indexes(&arr, (char *)"2026/01/01", indexes);
    EXPECT_EQ(indexes[0], -1);
    EXPECT_EQ(indexes[1], -1);
}

TEST(FirstHistoryIndex, PresentDate) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    first_history_index(&arr, 0, 2, 0, (char *)"2026/01/02", indexes, 0);
    EXPECT_EQ(indexes[0], 1);
    free_history(&arr);
}

TEST(FirstHistoryIndex, AbsentDateNonEmpty) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    first_history_index(&arr, 0, 2, 0, (char *)"2026/01/05", indexes, 0);
    EXPECT_EQ(indexes[0], -1);
    free_history(&arr);
}

TEST(FirstHistoryIndex, EmptyArray) {
    HistoryArray arr = {};
    int indexes[2] = {-1, -1};
    EXPECT_NO_CRASH(first_history_index(&arr, 0, -1, 0, (char *)"2026/01/01", indexes, 0));
}

TEST(LastHistoryIndex, PresentDate) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    last_history_index(&arr, 0, 2, 0, (char *)"2026/01/02", indexes, 0);
    EXPECT_EQ(indexes[1], 1);
    free_history(&arr);
}

TEST(LastHistoryIndex, AbsentDateNonEmpty) {
    const char *dates[] = {"2026/01/01", "2026/01/02", "2026/01/03"};
    const char *msgs[] = {"a", "b", "c"};
    HistoryArray arr = make_array(dates, msgs, 3);
    int indexes[2] = {-1, -1};
    last_history_index(&arr, 0, 2, 0, (char *)"2026/01/05", indexes, 0);
    EXPECT_EQ(indexes[1], -1);
    free_history(&arr);
}

TEST(LastHistoryIndex, EmptyArray) {
    HistoryArray arr = {};
    int indexes[2] = {-1, -1};
    EXPECT_NO_CRASH(last_history_index(&arr, 0, -1, 0, (char *)"2026/01/01", indexes, 0));
}

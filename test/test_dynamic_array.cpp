#include "utils/dynamic-array.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>

extern "C" void remove_history_log(char *file_name);

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

TEST(AddHistoryLog, FreshArray) {
    HistoryArray arr = {};
    add_history_log(&arr, (char *)"2026/01/01", (char *)"hello");
    ASSERT_EQ(arr.length, 1);
    ASSERT_NE(arr.history, nullptr);
    ASSERT_NE(arr.history[0], nullptr);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[0]->message, "hello");
    free_history(&arr);
}

TEST(AddHistoryLog, MultipleEntries) {
    HistoryArray arr = {};
    add_history_log(&arr, (char *)"2026/01/01", (char *)"one");
    add_history_log(&arr, (char *)"2026/01/02", (char *)"two");
    add_history_log(&arr, (char *)"2026/01/03", (char *)"three");
    ASSERT_EQ(arr.length, 3);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[0]->message, "one");
    EXPECT_STREQ(arr.history[1]->date, "2026/01/02");
    EXPECT_STREQ(arr.history[1]->message, "two");
    EXPECT_STREQ(arr.history[2]->date, "2026/01/03");
    EXPECT_STREQ(arr.history[2]->message, "three");
    free_history(&arr);
}

TEST(AddHistoryLog, DeepCopiesStrings) {
    char date[32];
    char msg[32];
    snprintf(date, sizeof(date), "2026/%s", "05/09");
    snprintf(msg, sizeof(msg), "%s", "original");
    HistoryArray arr = {};
    add_history_log(&arr, date, msg);
    snprintf(msg, sizeof(msg), "%s", "changed");
    EXPECT_STREQ(arr.history[0]->date, "2026/05/09");
    EXPECT_STREQ(arr.history[0]->message, "original");
    free_history(&arr);
}

TEST(AddHistoryLog, NullArrayDoesNotCrash) {
    EXPECT_NO_FATAL_FAILURE(add_history_log(nullptr, (char *)"2026/01/01", (char *)"x"));
}

TEST(RemoveHistoryLog, TruncatesExistingFile) {
    const char *path = "test/remove_tmp.log";
    FILE *f = fopen(path, "w");
    ASSERT_NE(f, nullptr);
    fputs("2026/01/01 hello\n", f);
    fclose(f);

    remove_history_log((char *)path);

    f = fopen(path, "r");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    remove(path);
    EXPECT_EQ(size, 0);
}

TEST(RemoveHistoryLog, MissingFileNoCrash) {
    const char *path = "test/does_not_exist_tmp.log";
    EXPECT_NO_FATAL_FAILURE(remove_history_log((char *)path));
    remove(path);
}

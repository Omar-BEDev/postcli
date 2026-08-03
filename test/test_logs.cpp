#include "io/logs/logs.h"
#include "utils/dynamic-array.h"
#include "utils/file-check.h"
#include "crash_guard.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>

extern "C" void read_file_logs(HistoryArray *history_arr, FILE *log_file);
extern "C" void make_log_dir(char *program_path, char *dir,
                             char *program_folder_name, char *log_file_name);
extern "C" void make_log_folder_dir(char *folder_path, char *dir,
                                    char *program_folder_name);

static HistoryArray read_file(const char *content) {
    const char *path = "test/logs_tmp.log";
    FILE *f = fopen(path, "w");
    fputs(content, f);
    fclose(f);

    HistoryArray arr = {};
    initialize_history_array(&arr);
    FILE *in = fopen(path, "r");
    read_file_logs(&arr, in);
    fclose(in);
    remove(path);
    return arr;
}

TEST(ReadFileLogs, ValidLines) {
    HistoryArray arr = read_file(
        "2026/01/01 first log\n"
        "2026/02/03 second log\n"
        "2026/12/31 last\n");
    ASSERT_EQ(arr.length, 3);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[0]->message, "first log");
    EXPECT_STREQ(arr.history[1]->date, "2026/02/03");
    EXPECT_STREQ(arr.history[1]->message, "second log");
    EXPECT_STREQ(arr.history[2]->date, "2026/12/31");
    EXPECT_STREQ(arr.history[2]->message, "last");
    free_history_array(&arr);
}

TEST(ReadFileLogs, EmptyFile) {
    HistoryArray arr = read_file("");
    EXPECT_EQ(arr.length, 0);
    free_history_array(&arr);
}

TEST(ReadFileLogs, EmptyLineInMiddle) {
    HistoryArray arr = read_file(
        "2026/01/01 first log\n"
        "\n"
        "2026/03/04 third log\n");
    ASSERT_EQ(arr.length, 2);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[1]->date, "2026/03/04");
    EXPECT_STREQ(arr.history[1]->message, "third log");
    free_history_array(&arr);
}

TEST(ReadFileLogs, ShortFirstLine) {
    HistoryArray arr = read_file(
        "x\n"
        "2026/01/01 ok\n");
    ASSERT_EQ(arr.length, 1);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[0]->message, "ok");
    free_history_array(&arr);
}

TEST(ReadFileLogs, LastLineWithoutNewline) {
    HistoryArray arr = read_file(
        "2026/01/01 first log\n"
        "2026/02/03 no newline");
    ASSERT_EQ(arr.length, 2);
    EXPECT_STREQ(arr.history[1]->date, "2026/02/03");
    EXPECT_STREQ(arr.history[1]->message, "no newline");
    free_history_array(&arr);
}

TEST(ExtractLogs, ExistingFile) {
    const char *path = "test/extract_tmp.log";
    FILE *f = fopen(path, "w");
    ASSERT_NE(f, nullptr);
    fputs("2026/01/01 hello\n", f);
    fclose(f);

    HistoryArray arr = {};
    initialize_history_array(&arr);
    extract_logs(&arr, (char *)path);
    remove(path);

    ASSERT_EQ(arr.length, 1);
    EXPECT_STREQ(arr.history[0]->date, "2026/01/01");
    EXPECT_STREQ(arr.history[0]->message, "hello");
    free_history_array(&arr);
}

TEST(ExtractLogs, NonexistentFileNoCrash) {
    HistoryArray arr = {};
    initialize_history_array(&arr);
    EXPECT_NO_FATAL_FAILURE(extract_logs(&arr, (char *)"test/does_not_exist_tmp.log"));
    EXPECT_EQ(arr.length, 0);
    free_history_array(&arr);
}

TEST(ReadFileLogs, UnwiredFunctionPointerCrashes) {
    HistoryArray arr = {};
    const char *path = "test/logs_unwired_tmp.log";
    FILE *f = fopen(path, "w");
    ASSERT_NE(f, nullptr);
    fputs("2026/01/01 hello\n", f);
    fclose(f);
    FILE *in = fopen(path, "r");
    ASSERT_NE(in, nullptr);

    EXPECT_NO_CRASH(read_file_logs(&arr, in));

    fclose(in);
    remove(path);
}

TEST(MakeLogDir, BuildsPath) {
    char path[512] = {0};
    make_log_dir(path, (char *)"/tmp/home", (char *)"postcli-tool", (char *)"logs.log");
    EXPECT_STREQ(path, "/tmp/home/postcli-tool/logs.log");
}

TEST(MakeLogFolderDir, BuildsPath) {
    char path[256] = {0};
    make_log_folder_dir(path, (char *)"/tmp/home", (char *)"postcli-tool");
    EXPECT_STREQ(path, "/tmp/home/postcli-tool");
}

TEST(LogPathGenerate, CreatesFolderAndFile) {
    const char *base = "test/logpath_home";
    mkdir(base, 0755);

    log_path_generate((char *)base);

    char expected[512];
    snprintf(expected, sizeof(expected), "%s/postcli-tool/logs.log", base);
    EXPECT_EQ(is_file_available(expected), 1);

    remove(expected);
    rmdir("test/logpath_home/postcli-tool");
    rmdir(base);
}

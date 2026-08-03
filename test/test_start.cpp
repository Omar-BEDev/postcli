#include "core/start/start.h"
#include "utils/file-check.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

TEST(Start, RunsAndCreatesLogFile) {
    setenv("HOME", "test/home_start_tmp", 1);
    mkdir("test/home_start_tmp", 0755);
    remove("logs.log");
    remove("test/home_start_tmp/postcli-tool/logs.log");
    rmdir("test/home_start_tmp/postcli-tool");

    testing::internal::CaptureStdout();
    start();
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(is_file_available("test/home_start_tmp/postcli-tool/logs.log"), 1);

    remove("test/home_start_tmp/postcli-tool/logs.log");
    rmdir("test/home_start_tmp/postcli-tool");
    rmdir("test/home_start_tmp");
}

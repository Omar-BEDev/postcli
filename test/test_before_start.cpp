#include "core/start/before-start.h"
#include "utils/file-check.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

TEST(MakeLogFile, CreatesLogFileWhenMissing) {
    setenv("HOME", "test/home_tmp", 1);
    mkdir("test/home_tmp", 0755);
    remove("test/home_tmp/postcli-tool/logs.log");
    rmdir("test/home_tmp/postcli-tool");

    make_log_file((char *)"make_log_file_missing_tmp.log");

    EXPECT_EQ(is_file_available("test/home_tmp/postcli-tool/logs.log"), 1);

    remove("test/home_tmp/postcli-tool/logs.log");
    rmdir("test/home_tmp/postcli-tool");
    rmdir("test/home_tmp");
}

TEST(MakeLogFile, NoOpWhenFileExists) {
    setenv("HOME", "test/home_tmp2", 1);
    mkdir("test/home_tmp2", 0755);
    const char *present = "make_log_file_exists_tmp.log";
    FILE *f = fopen(present, "w");
    ASSERT_NE(f, nullptr);
    fclose(f);

    make_log_file((char *)present);

    EXPECT_EQ(is_file_available("test/home_tmp2/postcli-tool/logs.log"), -1);

    remove(present);
    rmdir("test/home_tmp2");
}

TEST(ShowProgramLogo, PrintsLogo) {
    testing::internal::CaptureStdout();
    show_program_logo();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out.empty());
}

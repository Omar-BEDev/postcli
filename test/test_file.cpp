#include "utils/file-check.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <sys/stat.h>

TEST(IsFileAvailable, ExistingFile) {
    const char *path = "test/is_file_tmp.txt";
    FILE *f = fopen(path, "w");
    ASSERT_NE(f, nullptr);
    fputs("x", f);
    fclose(f);
    EXPECT_EQ(is_file_available(path), 1);
    remove(path);
}

TEST(IsFileAvailable, DirectoryIsNotRegularFile) {
    const char *path = "test/is_dir_tmp";
    mkdir(path, 0755);
    EXPECT_EQ(is_file_available(path), 0);
    rmdir(path);
}

TEST(IsFileAvailable, MissingFile) {
    EXPECT_EQ(is_file_available("test/does_not_exist_tmp"), -1);
}

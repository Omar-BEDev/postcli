#ifndef TEST_CRASH_GUARD_H
#define TEST_CRASH_GUARD_H

#include <sys/wait.h>
#include <unistd.h>
#include <gtest/gtest.h>

template <typename Fn>
static testing::AssertionResult RunGuarded(Fn fn) {
    pid_t pid = fork();
    if (pid < 0) {
        return testing::AssertionFailure() << "fork() failed";
    }
    if (pid == 0) {
        fn();
        _exit(0);
    }
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        return testing::AssertionFailure()
            << "process crashed with signal " << WTERMSIG(status);
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        return testing::AssertionFailure()
            << "process exited with status " << WEXITSTATUS(status);
    }
    return testing::AssertionSuccess();
}

#define EXPECT_NO_CRASH(...) EXPECT_TRUE(RunGuarded([&]() { __VA_ARGS__; }))

#endif

CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -g -Isrc 
TARGET = postcli

SRCS = src/main.c \
       src/core/history/history.c \
       src/core/date-compare.c \
       src/core/history/search.c \
       src/core/json_parsee.c \
       src/utils/dynamic-array.c \
       src/io/logs/logs.c \
       src/utils/file-check.c \
       src/core/start/before-start.c \
       src/core/start/start.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===================== Tests =====================
TEST_CXXFLAGS = -Wall -Wextra -g -Isrc
TEST_SRCS = $(filter-out src/main.c,$(SRCS))
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_CPP = test/test_main.cpp \
           test/test_date.cpp \
           test/test_dynamic_array.cpp \
           test/test_search.cpp \
           test/test_file.cpp \
           test/test_logs.cpp \
           test/test_before_start.cpp \
           test/test_start.cpp
TEST_OBJS += $(TEST_CPP:.cpp=.o)
TEST_TARGET = test/run_tests

test: $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(TEST_CXXFLAGS) -o $@ $(TEST_OBJS) -lgtest -pthread

%.o: %.cpp
	$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) test/*.o $(TEST_TARGET)
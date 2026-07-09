CC = gcc

CFLAGS = -Wall -Wextra -g -Isrc 
TARGET = postcli

SRCS = src/main.c \
       src/core/history/history.c \
       src/core/date-compare.c \
       src/core/history/search.c \
       src/core/json_parsee.c \
       src/utils/dynamic-array.c \
       src/io/logs/logs.c
       src/utils/file-check.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
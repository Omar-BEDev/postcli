CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = postcli

SRCS = src/main.c \
	   src/core/History.c \
       src/core/json_parsee.c \
       src/utils/dynamic-array.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

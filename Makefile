
CC = gcc
CFLAGS = -Wall -g
SRCS = a1.c chars.c tree.c
OBJS = $(SRCS:.c=.o)
TARGET = a1

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# implicit rule will compile .c -> .o; explicit if you prefer:
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
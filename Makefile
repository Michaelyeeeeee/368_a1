# Define a variable for the compiler
CC = gcc

# Define a variable for compiler flags
CFLAGS = -Wall -g

# Define the target executable name
TARGET = myprogram

# Rule to build the 'myprogram' target
$(TARGET): a1.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# Rule to clean up generated files
clean:
	rm -f $(TARGET)
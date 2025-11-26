# Makefile for FeLT 1.0 Release.

# I stole most of this from my own makefile from TTSM.  -Fraken.
# Should compile on pretty much any kind of BSD/Linux I would think.

CC = cc

CFLAGS = -Wall -Wextra
LDFLAGS = -lpthread 

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = felt

# Default target: builds the executable
all: $(EXECUTABLE)

# Rule to link the object files into the final executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Rule to compile each .c file into a .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: removes the compiled files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

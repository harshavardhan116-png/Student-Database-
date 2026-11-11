CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = dataBase
SOURCES = main.c input.c student.c database_file.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c student_db.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

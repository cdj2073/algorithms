CC = gcc
TARGET = student_info.out
SRCS = student_info_system.c red_black_tree.c
OBJECTS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

.PHONY: all clean
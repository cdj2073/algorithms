CC = gcc
TARGET = student_info.out
SRCS = student_info_system.c submodules.c red_black_tree.c
OBJECTS = $(SRCS:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

all: $(TARGET)

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

.PHONY: all clean
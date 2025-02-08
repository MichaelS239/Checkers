OBJECTS = src/main.o
SOURCES = src/main.cpp
NAME = ./checkers
CC = g++
DEBUG = -g -O0
RELEASE = -O3
debug: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o $(NAME)
release: $(OBJECTS)
	$(CC) $(RELEASE) $(OBJECTS) -o $(NAME)
.cpp.o:
	$(CC) $(DEBUG) -c $*.cpp -o $@
.PHONY: all clean valgrind gdb debug release
all:
	$(CC) $(RELEASE) $(SOURCES) -o $(NAME)
test:
	$(CC) $(DEBUG) $(TEST_SOURCES) -o $(NAME) $(GTEST_FLAGS)
clean:
	rm *.o $(NAME)
valgrind:
	valgrind --leak-check=full --track-origins=yes $(NAME)
gdb:
	gdb $(NAME)
run:
	$(NAME)
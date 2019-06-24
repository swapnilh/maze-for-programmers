CC = g++
CPPFLAGS = -Wall -std=c++11
DEPS = maze.hpp
OBJ = maze.o test.o
TARGET = maze
#RM = rm -rf
RM = rm -rf 

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(TARGET)

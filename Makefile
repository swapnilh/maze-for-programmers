CC = g++
CPPFLAGS = -Wall -std=c++11 -ggdb 
DEPS = cell.hpp util.hpp maze.hpp binary_tree.hpp sidewinder.hpp dijkstra.hpp aldous_broder.hpp 
OBJ = maze.o test.o cell.o
TARGET = maze
#RM = rm -rf
RM = rm -rf 

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(TARGET): $(OBJ) $(DEPS)
	$(CC) $(CPPFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(TARGET)

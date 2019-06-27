CC = g++
CPPFLAGS = -Wall -std=c++11 -ggdb# -DDEBUG 
DEPS = cell.hpp util.hpp maze.hpp maze_generator.hpp binary_tree.hpp sidewinder.hpp dijkstra.hpp aldous_broder.hpp hunt_and_kill.hpp 
OBJ = maze.o cell.o
TARGET = test deadend_stats
#RM = rm -rf
RM = rm -rf 

all: $(TARGET)

%.o: %.cpp $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $<

test: $(OBJ) test.o
	$(CC) $(CPPFLAGS) -o $@ $^

deadend_stats: $(OBJ) deadend_stats.o
	$(CC) $(CPPFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(TARGET) deadend_stats.o test.o

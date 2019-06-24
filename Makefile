CC = g++
CFLAGS = -Wall
DEPS = maze.hpp
OBJ = maze.o test.o
TARGET = maze
#RM = rm -rf
RM = rm -rf 

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(TARGET)

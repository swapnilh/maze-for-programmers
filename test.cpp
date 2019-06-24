#include <iostream>
#include "maze.hpp"

int main () {
  Maze basicOne(1, 1);
  basicOne.Display();
  Maze basicTwo(2, 2);
  basicTwo.Display();
	std::cout << "Opening the south wall of [1,1]" << std::endl;
	basicTwo.OpenWall(1, 1, Direction::South);
  basicTwo.Display();
	std::cout << "Closing the south wall of [1,1]" << std::endl;
	basicTwo.CloseWall(1, 1, Direction::South);
  basicTwo.Display();
  return 0;
}


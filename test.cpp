#include <iostream>
#include <cassert>
#include "maze.hpp"
#include "binary_tree.hpp"

int main () {
  Maze basicTwo(2, 2);
  basicTwo.Display();

	std::cout << "Opening the south wall of [1,1]" << std::endl;
	basicTwo.OpenWall(1, 1, Direction::South);
  basicTwo.Display();
	std::cout << "Closing the south wall of [1,1]" << std::endl;
	basicTwo.CloseWall(1, 1, Direction::South);
  basicTwo.Display();

	std::cout << "Opening the north wall of [1,1], should fail" << std::endl;
	assert(!basicTwo.OpenWall(1, 1, Direction::North));
  basicTwo.Display();

  Maze basicFive(5, 5);
  basicTwo.Display();
	std::cout << "Generating a perfect maze using binary_tree algorithm"
					  << std::endl;
	BinaryTreeCreator bt(basicFive);
	bt.Generate();
  basicFive.Display();
  return 0;
}


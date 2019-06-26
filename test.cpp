#include <iostream>
#include <cassert>
#include "maze.hpp"
#include "binary_tree.hpp"
#include "sidewinder.hpp"
#include "dijkstra.hpp"
#include "aldous_broder.hpp"

int main () {
  Maze basicTwo(2, 2);
  //basicFive.DebugDisplay();
  basicTwo.Display();

  Maze basicFive(5, 5);
  basicFive.Display();
	std::cout << "Generating a perfect maze using binary_tree algorithm"
					  << std::endl;
	BinaryTreeCreator bt(basicFive);
	bt.Generate();
  basicFive.Display();

	std::cout << "Resetting the maze" << std::endl;
  basicFive.Reset();

	std::cout << "Generating a perfect maze using sidewinder algorithm"
					  << std::endl;
	SidewinderCreator sw(basicFive);
	sw.Generate();
  basicFive.Display();

	std::cout << "Solving the maze using djikstra's algorithm" << std::endl;
	DijkstraSolver dj(basicFive);
	dj.Solve();

	std::cout << "Resetting the maze" << std::endl;
  basicFive.Reset();

	std::cout << "Generating a perfect maze using aldous-broder algorithm"
					  << std::endl;
	AldousBroderCreator ab(basicFive);
	ab.Generate();
  basicFive.Display();

	std::cout << "Solving the maze using djikstra's algorithm" << std::endl;
	dj.Reset();
	dj.Solve();


  return 0;
}

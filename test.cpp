#include <iostream>
#include <cassert>
#include "maze.hpp"
#include "binary_tree.hpp"
#include "sidewinder.hpp"
#include "dijkstra.hpp"
#include "aldous_broder.hpp"
#include "hunt_and_kill.hpp"

int main () {
  Maze basicTwo(2, 2);
  //basicFive.DebugDisplay();
  basicTwo.Display();

  Maze basicFive(10, 10);

  basicFive.Display();
	std::cout << "Generating a perfect maze using binary_tree algorithm"
					  << std::endl;
	BinaryTreeGenerator bt(basicFive);
	bt.Generate();
  basicFive.Display();
	std::cout << "Deadend Cells:" << basicFive.GetDeadendCells().size()
					  << std::endl;

	std::cout << "Resetting the maze" << std::endl;
  basicFive.Reset();

	std::cout << "Generating a perfect maze using sidewinder algorithm"
					  << std::endl;
	SidewinderGenerator sw(basicFive);
	sw.Generate();
  basicFive.Display();
	std::cout << "Deadend Cells:" << basicFive.GetDeadendCells().size()
					  << std::endl;

	std::cout << "Resetting the maze" << std::endl;
  basicFive.Reset();

	std::cout << "Generating a perfect maze using aldous-broder algorithm"
					  << std::endl;
	AldousBroderGenerator ab(basicFive);
	ab.Generate();
  basicFive.Display();
	std::cout << "Deadend Cells:" << basicFive.GetDeadendCells().size()
					  << std::endl;

	std::cout << "Resetting the maze" << std::endl;
  basicFive.Reset();

	std::cout << "Generating a perfect maze using hunt-and-kill algorithm"
					  << std::endl;
	HuntAndKillGenerator hk(basicFive);
	hk.Generate();
  basicFive.Display();
	std::cout << "Deadend Cells:" << basicFive.GetDeadendCells().size()
					  << std::endl;

	std::cout << "Solving the maze using djikstra's algorithm" << std::endl;
	DijkstraSolver dj(basicFive);
	dj.Reset();
	dj.Solve();

  return 0;
}

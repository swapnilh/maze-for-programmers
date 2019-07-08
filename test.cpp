#include <iostream>
#include <cassert>
#include "maze.hpp"
#include "maze_generator.hpp"
#include "binary_tree.hpp"
#include "sidewinder.hpp"
#include "dijkstra.hpp"
#include "aldous_broder.hpp"
#include "hunt_and_kill.hpp"
#include "recursive_backtrack.hpp"

constexpr auto GRID_DIM = 6;

int main () {

  Maze test_maze(GRID_DIM, GRID_DIM);
	std::vector<MazeGenerator*> generators;
	generators.push_back(new BinaryTreeGenerator(test_maze));
	generators.push_back(new SidewinderGenerator(test_maze));
	generators.push_back(new AldousBroderGenerator(test_maze));
	generators.push_back(new HuntAndKillGenerator(test_maze));
	generators.push_back(new RecursiveBacktrackGenerator(test_maze));
	DijkstraSolver dj(test_maze);

	for (auto generator : generators) {
		std::cout << "Generating a perfect maze using "
					  <<  generator->GetName() << " algorithm" << std::endl;
		generator->Generate();
		test_maze.Display();	
		std::cout << "Deadend Cells:" << test_maze.GetDeadendCells().size()
						  << std::endl;
		
		std::cout << "Solving the maze using djikstra's algorithm" << std::endl;
		dj.Reset();
		dj.Solve();
		
		std::cout << "Resetting the maze" << std::endl;
		test_maze.Reset();
	}
  return 0;
}

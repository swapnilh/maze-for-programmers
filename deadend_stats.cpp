#include <iostream>
#include <vector>
#include <cassert>
#include "maze.hpp"
#include "maze_generator.hpp"
#include "binary_tree.hpp"
#include "sidewinder.hpp"
#include "dijkstra.hpp"
#include "aldous_broder.hpp"
#include "hunt_and_kill.hpp"

constexpr auto GRID_DIM = 20;
constexpr auto ITERATIONS = 100;

int main () {

  Maze basicTwenty(GRID_DIM, GRID_DIM);
	std::vector<MazeGenerator*> generators;
	generators.push_back(new BinaryTreeGenerator(basicTwenty));
	generators.push_back(new SidewinderGenerator(basicTwenty));
	generators.push_back(new AldousBroderGenerator(basicTwenty));
	generators.push_back(new HuntAndKillGenerator(basicTwenty));

	for (auto generator : generators) {
		int deadend_count = 0;
		for (int iter = 0; iter < ITERATIONS; iter++) {
			generator->Generate();
			deadend_count += basicTwenty.GetDeadendCells().size();
			basicTwenty.Reset();
		}
		auto avg_deadend_count = deadend_count / ITERATIONS;
		std::cout << generator->GetName() << " : " << avg_deadend_count << "/"
			<< GRID_DIM*GRID_DIM << " ("
			<< avg_deadend_count*100.0 / (GRID_DIM*GRID_DIM) << "%)"
			<< std::endl;
	}
	return 0;
}

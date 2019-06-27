#include <iostream>
#include <chrono>
#include <vector>
#include <cassert>
#include "maze.hpp"
#include "maze_generator.hpp"
#include "binary_tree.hpp"
#include "sidewinder.hpp"
#include "dijkstra.hpp"
#include "aldous_broder.hpp"
#include "hunt_and_kill.hpp"
#include "recursive_backtrack.hpp"

constexpr auto GRID_DIM = 20;
constexpr auto ITERATIONS = 100;

int main () {

  Maze test_maze(GRID_DIM, GRID_DIM);
	std::vector<MazeGenerator*> generators;
	generators.push_back(new BinaryTreeGenerator(test_maze));
	generators.push_back(new SidewinderGenerator(test_maze));
	generators.push_back(new AldousBroderGenerator(test_maze));
	generators.push_back(new HuntAndKillGenerator(test_maze));
	generators.push_back(new RecursiveBacktrackGenerator(test_maze));
	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

	for (auto generator : generators) {
		int deadend_count = 0;
    start = std::chrono::high_resolution_clock::now();
		for (int iter = 0; iter < ITERATIONS; iter++) {
			generator->Generate();
			deadend_count += test_maze.GetDeadendCells().size();
			test_maze.Reset();
		}
    stop = std::chrono::high_resolution_clock::now();
		auto avg_deadend_count = deadend_count / ITERATIONS;
		std::cout << generator->GetName() << " : " << avg_deadend_count << "/"
			<< GRID_DIM*GRID_DIM << " ("
			<< avg_deadend_count*100.0 / (GRID_DIM*GRID_DIM) << "%)"
			<< std::endl;
		auto latency = std::chrono::duration_cast<std::chrono::nanoseconds>
			(stop-start).count();
		std::cout << "Latency: " << latency/1000000.0 << " ms\n";
	}
	return 0;
}

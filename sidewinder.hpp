#ifndef SIDEWINDER_HPP
#define SIDEWINDER_HPP

#include <iostream>
#include <random>
#include "maze.hpp"
	
class SidewinderCreator {
	Maze& maze_;
	std::mt19937 rng_;
	
public:
	SidewinderCreator (Maze& maze) : maze_(maze), rng_((std::random_device())())
	{
	}

	void Generate() {
		// Generates random integers from the set [1, 2].
    std::uniform_int_distribution<int> dist2(1,2);

	  // Perform the sidewinder algo for all cells except those in top row.
		for (int row = 0; row < maze_.GetNumRows() - 1; row++) {
		int run_start = 0;
			for (int col = 0; col < maze_.GetNumCols(); col++) {
				int rand_int = dist2(rng_);

				if (rand_int == 2) { // Open East Wall if possible.
					if(!maze_.Link(row, col, Direction::East)) {
						rand_int = 1;
					}
				}
				if (rand_int == 1) { // Open North Wall for previous run, if possible.
					std::uniform_int_distribution<int> dist_run(run_start, col);
					int rand_col = dist_run(rng_);
					maze_.Link(row, rand_col, Direction::North);
					run_start = col+1;
				}
			}
		}
		// Open the East Wall for all cells in the top row.
		for (int col = 0; col < maze_.GetNumCols(); col++) {
			maze_.Link(maze_.GetNumRows()-1, col, Direction::East);
		}
	}

};

#endif // SIDEWINDER_HPP

#ifndef ALDOUS_BRODER_HPP
#define ALDOUS_BRODER_HPP

#include <iostream>
#include <unordered_set>
#include "maze_generator.hpp"
	
class AldousBroderGenerator: public MazeGenerator {
public:
	AldousBroderGenerator (Maze& maze) : MazeGenerator(maze, "AldousBroder")
		{}

	void Generate() override {
		unsigned int num_cells = maze_.GetNumRows() * maze_.GetNumCols();
		int num_cols = maze_.GetNumCols();

		// Pick a random starting cell.
    std::uniform_int_distribution<int> distCell (0, num_cells-1);
		int rand_coords = distCell(rng_);
		Cell* current_cell = maze_.GetCell(rand_coords/num_cols, 
																		rand_coords%num_cols);

		std::unordered_set <int> visited_cells;
			
		std::uniform_int_distribution<int> distDir(0,3);
		
		int wasted_iterations = 0;
		// Loop till all cells are visited.
		while (visited_cells.size() < num_cells) {
			wasted_iterations++;
			visited_cells.insert(HashCell(current_cell, num_cols));
			// Choose a random direction.
			int rand_dir = distDir(rng_);
			Cell* next_cell = current_cell->GetNeighbor(IntToDirection(rand_dir));
			if (next_cell == nullptr)	continue;
			
			// If not visited before, link the two cells.
			if (visited_cells.find(HashCell(next_cell, num_cols))
					== visited_cells.end()) {
				current_cell->LinkCell(IntToDirection(rand_dir));
			  NOTE ("Wasted Iterations:%d\n", wasted_iterations);	
				wasted_iterations=0;
			}
			current_cell = next_cell;
		}
	}
};

#endif // ALDOUS_BRODER_HPP

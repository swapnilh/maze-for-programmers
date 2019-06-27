#ifndef RECURSIVE_BACKTRACK_HPP
#define RECURSIVE_BACKTRACK_HPP

#include <iostream>
#include <cassert>
#include <unordered_set>
#include <stack>
#include "maze_generator.hpp"
	
class RecursiveBacktrackGenerator: public MazeGenerator {
public:
	RecursiveBacktrackGenerator (Maze& maze) 
		: MazeGenerator(maze, "RecursiveBacktrack")
		{}

	void Generate() override {
		unsigned int num_cells = maze_.GetNumRows() * maze_.GetNumCols();
		int num_cols = maze_.GetNumCols();

		// Pick a random starting cell.
    std::uniform_int_distribution<int> distCell (0, num_cells-1);
		int rand_coords = distCell(rng_);
		Cell* current_cell = maze_.GetCell(rand_coords/num_cols, 
																		rand_coords%num_cols);

		// Track visited cells.
		std::unordered_set <int> visited_cells;

		// Maintain stack for backtracking.
		std::stack<Cell*> cell_stack;

		std::uniform_int_distribution<int> distDir(0,3);
		
		// Loop till all cells are visited.
		while (visited_cells.size() < num_cells) {
			NOTE("Visited: %lu / %d\n", visited_cells.size(), num_cells);
			NOTE("Current Cell: {%d,%d}\n", current_cell->row, current_cell->col);
			#ifdef DEBUG
			maze_.Display();
			#endif
			visited_cells.insert(HashCell(current_cell, num_cols));

			// Is any neighbor unvisited?
			auto neighbors = current_cell->GetNeighbors();
			int unvisited_neighbors = 0;

			for (auto neighbor : neighbors) {
				if (neighbor != nullptr &&
					  visited_cells.find(HashCell(neighbor, num_cols)) == visited_cells.end()) {
					// Shift all unvisited neighbors to the beginning of the vector.
					neighbors[unvisited_neighbors] = neighbor;
					unvisited_neighbors++;
				}
			}

			if (unvisited_neighbors > 0) {
				NOTE("Unvisited Neighbors:%d\n", unvisited_neighbors);
				// Choose a random direction.
				int rand_dir = 5; // Bigger than 4, max number of unvisited neighbors.
				do {
					rand_dir = distDir(rng_);
				} while (rand_dir >= unvisited_neighbors);
				Cell* next_cell = neighbors[rand_dir];
				assert (next_cell != nullptr);
				current_cell->LinkCell(next_cell);
				NOTE ("Linking Current Cell to Next Cell!\n");
				cell_stack.push(current_cell);
				// Update current cell
				current_cell = next_cell;
				continue;
			}
			// Backtrack
			NOTE("Backtracking!\n");
			current_cell = cell_stack.top();
			cell_stack.pop();
		}
	}
};

#endif // RECURSIVE_BACKTRACK_HPP

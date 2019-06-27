#ifndef HUNT_AND_KILL_HPP
#define HUNT_AND_KILL_HPP

#include <iostream>
#include <random>
#include <cassert>
#include <unordered_set>
#include <tuple>
#include "maze.hpp"
	
class HuntAndKillCreator {
	Maze& maze_;
	std::mt19937 rng_;
	
public:
	HuntAndKillCreator (Maze& maze) : maze_(maze), rng_((std::random_device())())
	{}

	void Generate() {
		unsigned int num_cells = maze_.GetNumRows() * maze_.GetNumCols();
		int num_cols = maze_.GetNumCols();

		// Pick a random starting cell.
    std::uniform_int_distribution<int> distCell (0, num_cells-1);
		int rand_coords = distCell(rng_);
		Cell* current_cell = maze_.GetCell(rand_coords/num_cols, 
																		rand_coords%num_cols);

		std::unordered_set <int> visited_cells;
			
		std::uniform_int_distribution<int> distDir(0,3);
		
		// Loop till all cells are visited.
		while (visited_cells.size() < num_cells) {
			NOTE("Visited: %lu / %d\n", visited_cells.size(), num_cells);
			NOTE("Current Cell: {%d,%d}\n", current_cell->row, current_cell->col);
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
				current_cell = next_cell;
				NOTE ("Linking Current Cell to Next Cell!\n");
				continue;
			}
			// Hunt Phase!
			NOTE ("Hunting Phase begins!\n");
			bool break_out = false;
			for (int row = maze_.GetNumRows()-1; row>=0; row--) {
				for (int col = 0; col < num_cols; col++) {
					// Looking for an unvisited cell surrounded by at least visited cell.
					current_cell = maze_.GetCell(row, col);
					if (visited_cells.find(HashCell(current_cell, num_cols))
						 != visited_cells.end()) {
						continue;
					}
					NOTE("Found unvisited cell: {%d,%d}!\n", current_cell->row,
							 current_cell->col);

					// Does the unvisited cell have any visited neighbors?
					neighbors = current_cell->GetNeighbors();
					int visited_neighbors = 0;

					for (auto neighbor : neighbors) {
						if (neighbor != nullptr && 
							  visited_cells.find(HashCell(neighbor, num_cols))
							  != visited_cells.end()) {
							// Shift all unvisited neighbors to the beginning of the vector.
							neighbors[visited_neighbors] = neighbor;
							visited_neighbors++;
						}
					}
					NOTE("Visited Neighbors:%d\n", visited_neighbors);
					if (visited_neighbors == 0) {
						continue;
					}
					// Choose a random direction.
					int rand_dir = 5; // Bigger than 4, max number of visited neighbors.
					do {
						rand_dir = distDir(rng_);
					} while (rand_dir >= visited_neighbors);
					Cell* next_cell = neighbors[rand_dir];
					assert (next_cell != nullptr);
					current_cell->LinkCell(next_cell);
					NOTE ("HUNT:: Linking {%d,%d} to {%d,%d}!\n", 
								current_cell->row, current_cell->col,
								next_cell->row, next_cell->col);
					break_out = true;
					break;
				}
				if (break_out) break;
			}
		}
	}
};

#endif // HUNT_AND_KILL_HPP

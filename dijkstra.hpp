#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include "maze.hpp"
	
class DijkstraSolver {
	Maze& maze_;
	// -1 for unvisited, -2 for blocked, else distance from source.
	std::vector<std::vector<int> > flood_fill_;

	void SolveHelper(int row, int col, int distance) {
		// Return if invalid cell or already visited.
		if (maze_.IsInvalid(row, col) || flood_fill_[row][col] != -1)
			return;

		flood_fill_[row][col] = distance;

		auto* const current_cell = maze_.GetCell(row, col);
		auto neighbors = current_cell->GetNeighbors();
		for (auto neighbor : neighbors) {
			if (current_cell->Linked(neighbor))
				SolveHelper(neighbor->row, neighbor->col, distance+1);
		}
	}

	// "Star"s all cells on shortest path from source to target
	// once flood_fill_ is populated.	
	void TracePath(Cell* source, Cell* target) {
		if (source == nullptr || target == nullptr) 
			return;
	
		source->starred = true;
		auto* current_cell = source; 

		while(current_cell != target) {
			auto neighbors = current_cell->GetNeighbors();
			for (auto* neighbor : neighbors) {
				if (current_cell->Linked(neighbor)) {
					if (flood_fill_[neighbor->row][neighbor->col]
							< flood_fill_[current_cell->row][current_cell->col]) {
						current_cell = neighbor;
						break;
					}
				}
			}
			current_cell->starred = true;
		}	
	}

	void Print() {
		for (int row = 2*maze_.GetNumRows(); row >= 0; row--) {
			for (int col = 0; col < 2*maze_.GetNumCols()+1; col++) {
				std::cout << std::setw(2) << flood_fill_[row][col] << " ";
			}
			std::cout << std::endl;
		}	
	}

public:
	DijkstraSolver (Maze& maze) : 
		maze_(maze), flood_fill_(maze_.GetNumRows(),
														 std::vector<int>(maze_.GetNumCols(), -1)) 
	{}

	void Reset() {
		for (int row = 0; row < maze_.GetNumRows(); row++) {
			for (int col = 0; col < maze_.GetNumCols(); col++) {
				flood_fill_[row][col] = -1;
			}
		}
	}

	// Finds a path from the NW corner to the SE corner.
	void Solve() {
		Cell* const nw_corner = maze_.GetCell(maze_.GetNumRows()-1, 0);
		Cell* const se_corner = maze_.GetCell(0, maze_.GetNumCols()-1);
		SolveHelper(nw_corner->row, nw_corner->col, 0);
		TracePath(se_corner, nw_corner);
		maze_.Display();
	}

};

#endif // DIJKSTRA_HPP

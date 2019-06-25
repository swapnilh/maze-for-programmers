#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "maze.hpp"
	
class DijkstraSolver {
	Maze& maze_;
	// -1 for unvisited, -2 for blocked, else distance from source.
	std::vector<std::vector<int> > flood_fill_;

	void SolveHelper(Cell cell, int distance) {
		// Return if invalid cell or already visited.
		if (maze_.IsInvalid(cell) || flood_fill_[cell.row][cell.col] != -1)
			return;

		// Mark blocked if appropriate.
		if (maze_.IsClosed(cell)) {
				flood_fill_[cell.row][cell.col] = -2;
				return;
		}

		flood_fill_[cell.row][cell.col] = distance;

		SolveHelper({cell.row+1, cell.col}, distance+1);
		SolveHelper({cell.row-1, cell.col}, distance+1);
		SolveHelper({cell.row, cell.col+1}, distance+1);
		SolveHelper({cell.row, cell.col-1}, distance+1);
	}
	
	// Makes all cells on the path = 0
	bool TracePath(Cell cell, int distance) {
		if (maze_.IsInvalid(cell)) 
			return false;

		if (flood_fill_[cell.row][cell.col] == -2
				 || flood_fill_[cell.row][cell.col] == 0) {
			return false;
		}		

		int curr_distance = flood_fill_[cell.row][cell.col];
		if (curr_distance >=0 && curr_distance <= distance) {
			flood_fill_[cell.row][cell.col] = 0;
			if (!TracePath({cell.row+1, cell.col}, curr_distance)) {
				if (!TracePath({cell.row-1, cell.col}, curr_distance)) {
					if (!TracePath({cell.row, cell.col+1}, curr_distance)) {
						if (!TracePath({cell.row, cell.col-1}, curr_distance)) {
						}
					}
				}
			}
		  return true;
		}
		else {
			return false;
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
		maze_(maze), flood_fill_(2*maze_.GetNumRows()+1,
														 std::vector<int>(2*maze_.GetNumCols()+1, -1)) 
	{}

	// Finds a path from the NW corner to the SE corner.
	void Solve() {
		Cell nw_corner {2*maze_.GetNumRows()-1, 1};
		Cell se_corner {1, 2*maze_.GetNumCols()-1};
		SolveHelper(nw_corner, 0);
		TracePath(se_corner, flood_fill_[se_corner.row][se_corner.col]+1);
		DisplayPath();
	}

	void DisplayPath() {
		for (int row = 2*maze_.GetNumRows(); row >= 0; row--) {
			for (int col = 0; col < 2*maze_.GetNumCols()+1; col++) {
				char symbol =  (flood_fill_[row][col] == 0) ? '.'
										 : ((flood_fill_[row][col] > 0) ? ' ' : '#');
				std::cout << symbol << symbol;
			}
			std::cout << std::endl;
		}
	}

};

#endif // DIJKSTRA_HPP

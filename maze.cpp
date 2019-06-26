#include <iostream>
#include "maze.hpp"

void Maze::DebugDisplay() {
		for (int row = 0; row < num_rows_; row++)
			for (int col = 0; col < num_cols_; col++) 
				cells_[row][col]->PrintCell();
}

void Maze::Display() {
  for (int row = num_rows_-1; row >= 0; row--) { 
		// Print north wall
    for (int col = 0; col < num_cols_; col++) {
			Cell* cell = cells_[row][col];	
			Cell* neighbor = cell->GetNeighbor(Direction::North);
			std::cout << "+";
			// If neighbor does not exist or is blocked off, display wall.
			if (neighbor == nullptr || !cell->Linked(neighbor)) {
				std::cout << "---";
			} else {
				std::cout << "   ";
			}	
    }
		std::cout << "+" << std::endl;
		// Print west wall
    for (int col = 0; col < num_cols_; col++) {
			Cell* cell = cells_[row][col];	
			Cell* neighbor = cell->GetNeighbor(Direction::West);
			// If neighbor does not exist or is blocked off, display wall.
			if (neighbor == nullptr || !cell->Linked(neighbor)) {
				std::cout << "|";
			} else {
				std::cout << " ";
			}
			if (cell->starred)
				std::cout << " * ";
			else	
				std::cout << "   ";
    }
		std::cout << "|" << std::endl;
  }
	// Print South wall
	for (int col = 0; col < num_cols_; col++) {
			std::cout << "+---";
	}
 	std::cout << "+" << std::endl;
}

bool Maze::Unlink (int row, int col, Direction dir) {
	Cell* cell = cells_[row][col];
	Cell* neighbor = cell->GetNeighbor(dir) ;
	
	// If neighbor does not exist	
	if (neighbor == nullptr) {
		return false;
	}
	
	cell->UnlinkCell(neighbor);
	
	return true;
}

bool Maze::Link (int row, int col, Direction dir) {
	Cell* cell = cells_[row][col];
	Cell* neighbor = cell->GetNeighbor(dir) ;

	// If neighbor does not exist	
	if (neighbor == nullptr) {
		return false;
	}
	
	cell->LinkCell(neighbor);
	
	return true;
}

void Maze::Reset () {
	for (int row = 0; row < num_rows_; row++) {
		for (int col = 0; col < num_cols_; col++) {
			auto* cell = cells_[row][col];
			cell->starred = false;
			cell->north_cell = (IsInvalid(row+1, col))? nullptr: cells_[row+1][col];
			cell->east_cell =  (IsInvalid(row, col+1))? nullptr : cells_[row][col+1];
			cell->west_cell =  (IsInvalid(row, col-1))? nullptr : cells_[row][col-1];
			cell->south_cell = (IsInvalid(row-1, col))? nullptr : cells_[row-1][col];
			cell->UnlinkCell(cell->north_cell);
			cell->UnlinkCell(cell->east_cell);
			cell->UnlinkCell(cell->west_cell);
			cell->UnlinkCell(cell->south_cell);
		}
	}
}

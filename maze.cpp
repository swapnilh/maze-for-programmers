#include <iostream>
#include "maze.hpp"

Cell Maze::GetWall(Cell cell, Direction dir) {
	if (cell.row >= num_rows_ || cell.row < 0
			|| cell.col >= num_cols_ || cell.col < 0) {
		std::cerr << "Cell dimensions incorrect: ["
			<< cell.row  << "," << cell.col << "]" << std::endl;
		return  {-1, -1};
	}

	Cell actual_cell = {2*cell.row + 1, 2*cell.col + 1};

	return actual_cell.GetNeighbor(dir);
}

void Maze::Display() {
  for (int row = 2*num_rows_; row >= 0; row--) {
    for (int col = 0; col < 2*num_cols_+1; col++) {
      char symbol = (cells_[row][col] == false) ? ' ' : '#';
      std::cout << symbol << symbol;
    }
    std::cout << std::endl;
  }
}

bool Maze::CloseWall (int row, int col, Direction dir) {
	
	Cell wall = GetWall({row, col}, dir);
	
	// If any error in input, return false.
	if (wall.row == -1 || wall.col == -1) {
		return false;
	}

	// If cell border is also the external border of the maze, return false.
	if (IsInvalid(wall))
		return false;

	cells_[wall.row][wall.col] = true;
	
	return true;
}

bool Maze::OpenWall (int row, int col, Direction dir) {
	
	Cell wall = GetWall({row, col}, dir);
	
	// If any error in input, return false.
	if (wall.row == -1 || wall.col == -1) {
		return false;
	}
	
	// If cell border is also the external border of the maze, return false.
	if (IsInvalid(wall))
		return false;

	cells_[wall.row][wall.col] = false;
	
	return true;
}

void Maze::Reset () {
	// Closing all east-west walls.
	for (int row = 0; row < 2*num_rows_+1; row+=2) {
		for (int col = 0; col < 2*num_cols_+1; col++) {
			cells_[row][col] = true;
		}
	}
	// Closing all north-south walls.
	for (int col = 0; col < 2*num_cols_+1; col+=2) {
		for (int row = 0; row < 2*num_rows_+1; row++) {
			cells_[row][col] = true;
		}
	}
}

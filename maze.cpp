#include <iostream>
#include "maze.hpp"

Cell Maze::GetWall(Cell cell, Direction dir) {
	int actual_row = 2*cell.row + 1;
	int actual_col = 2*cell.col + 1;

	if (actual_row >= num_rows_ || actual_row < 0
			|| actual_col >= num_cols_ || actual_col < 0) {
		std::cerr << "Cell dimensions incorrect: ["
			<< cell.row  << "," << cell.col << "]" << std::endl;
		return  {-1, -1};
	}

	switch (dir) {
		case Direction::North:
			actual_row += 1;
			break;
		case Direction::East:
			actual_col += 1;
			break;
		case Direction::West:
			actual_col -= 1;
			break;
		case Direction::South:
			actual_row -= 1;
			break;
		default:
			std::cerr << "Illegal Direction encountered" << std::endl;
			return {-1, -1};
	}

	return {actual_row, actual_col};

}

void Maze::Display() {
  for (int row = 0; row < num_rows_; row++) {
    for (int col = 0; col < num_cols_; col++) {
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
	if (wall.row >= num_rows_ || wall.row <= 0
			|| wall.col >= num_cols_ || wall.col <= 0) {
		return false;
	}

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
	if (wall.row >= num_rows_ || wall.row <= 0
			|| wall.col >= num_cols_ || wall.col <= 0) {
		return false;
	}

	cells_[wall.row][wall.col] = false;
	
	return true;
}

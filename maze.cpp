#include <iostream>
#include "maze.hpp"

Cell Maze::GetWall(Cell cell, Direction dir) {
	if (cell.row >= num_rows_ || cell.row < 0
			|| cell.col >= num_cols_ || cell.col < 0) {
		std::cerr << "Cell dimensions incorrect: ["
			<< cell.row  << "," << cell.col << "]" << std::endl;
		return  {-1, -1};
	}

	int actual_row = 2*cell.row + 1;
	int actual_col = 2*cell.col + 1;

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
	if (IsOuterWall(wall))
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
	if (IsOuterWall(wall))
		return false;

	cells_[wall.row][wall.col] = false;
	
	return true;
}

#ifndef MAZE_HPP
#define MAZE_HPP

#include<vector>

enum class Direction {
	North,
	East,
	West,
	South
};

struct Cell {
	int row;
	int col;
	Cell (int row_in, int col_in) : row(row_in), col(col_in) {
	}
	
	Cell GetNeighbor(Direction dir) {
		switch (dir) {
			case Direction::North:
				return {row+1, col};
				break;
			case Direction::East:
				return {row, col+1};
				break;
			case Direction::West:
				return {row, col-1};
				break;
			case Direction::South:
				return {row-1, col};
				break;
			default:
				return {-1, -1};
		}
	}

	// We need both associative and iterative access to neighbors. 
		std::vector<Cell>	GetNeighbors () {
		std::vector<Cell> neighbor_list;
		neighbor_list.push_back(GetNeighbor(Direction::North));
		neighbor_list.push_back(GetNeighbor(Direction::East));
		neighbor_list.push_back(GetNeighbor(Direction::West));
		neighbor_list.push_back(GetNeighbor(Direction::South));
		return neighbor_list;
	}
};

// The M x N maze is represented as 2M+1 x 2N+1 as walls are stored as cells.
// All odd indices are real cells, even indices are walls (open or closed).
class Maze {

	// Stores the number of rows and the cols of the original maze
	// and does not include the count of walls.
  int num_rows_;
  int num_cols_;

  // true = closed, false = open.
  // odd indices cannot be closed as they are real cells. 
  // TODO: store only walls and not cells.
  std::vector<std::vector<bool> > cells_; 

	// Returns the "dir"-side wall of the input cell.
	Cell GetWall(Cell cell, Direction dir);

public:
  Maze(int num_rows, int num_cols) :
    num_rows_(num_rows), num_cols_(num_cols),
    cells_(2*num_rows+1, std::vector<bool>(2*num_cols+1, false)) {
		Reset();
  }
	
	int GetNumRows () {
		return num_rows_;
	}

	// Returns the number of cols
	int GetNumCols () {
		return num_cols_;
	}

	// Identifies invalid cells, including those on the outer edge of maze.
	bool IsInvalid(Cell cell) {
		if (cell.row >= 2*num_rows_ || cell.row <= 0
				|| cell.col >= 2*num_cols_ || cell.col <= 0) {
			return true;
		}
		return false;
	}
 
	// Resolve internal vs external coordinates.
	bool IsClosed(Cell cell) {
		return cells_[cell.row][cell.col];
	}
 
	// ASCII-based display of the maze	
  void Display();

	// Close the "dir"-side border of the cell at [row, col].
	// Note that we only use scaled cell coordinates internally.
	bool CloseWall (int row, int col, Direction dir);

	// Open the "dir"-side border of the cell at [row, col].
	// Note that we only use scaled cell coordinates internally.
	bool OpenWall (int row, int col, Direction dir);

	// Close all walls of the maze.
	void Reset ();

};

#endif // MAZE_HPP

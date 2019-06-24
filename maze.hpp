#ifndef MAZE_HPP
#define MAZE_HPP

#include<vector>
#include<tuple>

enum class Direction {
	North,
	East,
	West,
	South
};

struct Cell {
	int row;
	int col;

	Cell (int row_in, int col_in) : row(row_in), col(col_in) {}
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
	
	// Is the cell part of the outer wall of the maze?
	bool IsOuterWall(Cell cell) {
		if (cell.row >= 2*num_rows_ || cell.row <= 0
				|| cell.col >= 2*num_cols_ || cell.col <= 0) {
			return true;
		}
		return false;
	}
  
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

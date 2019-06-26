#ifndef MAZE_HPP
#define MAZE_HPP

#include<vector>
#include<unordered_set>
#include "cell.hpp"

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
  std::vector<std::vector<Cell*> > cells_; 

public:
  Maze(int num_rows, int num_cols) :
    num_rows_(num_rows), num_cols_(num_cols),
    cells_(num_rows, std::vector<Cell*>(num_cols, nullptr)) {
		for (int row = 0; row < num_rows_; row++) {
			for (int col = 0; col < num_cols_; col++) {
				cells_[row][col] = new Cell(row, col);
			}
		}
		Reset();
  }
	
	int GetNumRows () {
		return num_rows_;
	}

	// Returns the number of cols
	int GetNumCols () {
		return num_cols_;
	}

	Cell* const GetCell (int row, int col) {
		return cells_[row][col];
	}

	// Identifies invalid cells, including those on the outer edge of maze.
	bool IsInvalid(int row, int col) {
		if (row >= num_rows_ || row < 0
				|| col >= num_cols_ || col < 0) {
			return true;
		}
		return false;
	}

	// Text-based display of cells in the maze	
  void DebugDisplay();

	// ASCII-based display of the maze	
  void Display();

	// Close the "dir"-side border of the cell at [row, col].
	bool Unlink (int row, int col, Direction dir);

	// Open the "dir"-side border of the cell at [row, col].
	bool Link (int row, int col, Direction dir);

	// Close all walls of the maze.
	void Reset ();

};

#endif // MAZE_HPP

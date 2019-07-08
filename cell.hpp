#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <unordered_map>
#include "util.hpp"

struct Cell {
	int row;
	int col;
	// Starred cells are displayed specially, used for displaying paths..
	bool starred;

	// Linked Cells
	std::vector<Cell*> links;

	// Neighbors	
	std::unordered_map<Direction, Cell*, EnumClassHash> neighbors;

	Cell (int row_in, int col_in) : row(row_in), col(col_in), starred(false)
	 {}
	
	// Checks whether the cell is linked to this cell.
	bool Linked (Cell* cell);

	// Returns false if neighbor does not exist 
	bool LinkCell (Direction dir);

	// Returns false if neighbor does not exist
	bool UnlinkCell (Direction dir);

	// Returns false if neighbor does not exist 
	bool LinkCell (Cell* cell);

	// Returns false if neighbor does not exist
	bool UnlinkCell (Cell* cell);

	// Fails if neighbor exists in direction dir.
	bool AddNeighbor (Direction dir, Cell* cell);
	
	// Fails if no neighbor in direction dir.
	bool DeleteNeighbor (Direction dir);

	// We need both associative and iterative access to neighbors. 
	Cell* GetNeighbor (Direction dir);

	std::vector<Cell*> GetNeighbors ();

	void PrintCell(bool print_neighbors = true);
};
	
inline bool operator==(const Cell& lhs, const Cell& rhs) {
	return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

inline int HashCell (Cell* cell, int num_cols) {
	return cell->row*num_cols + cell->col;
}
#endif // CELL_HPP

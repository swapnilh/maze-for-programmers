#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include "util.hpp"

struct Cell {
	int row;
	int col;
	// Starred cells are displayed specially, used for displaying paths..
	bool starred;

	// Linked Cells
	std::vector<Cell*> links;

	// Neighbors	
	Cell* north_cell;
	Cell* south_cell;
	Cell* east_cell;
	Cell* west_cell;

	Cell (int row_in, int col_in) : row(row_in), col(col_in), starred(false)
	 {}
	
	// Checks whether the cell is linked to this cell.
	bool Linked (Cell* cell);

	void LinkCell (Cell* cell);

	void UnlinkCell (Cell* cell);

	// We need both associative and iterative access to neighbors. 
	Cell* GetNeighbor (Direction dir);

	std::vector<Cell*> GetNeighbors ();

	void PrintCell(bool print_neighbors = true);
};
	
inline bool operator==(const Cell& lhs, const Cell& rhs) {
	return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

#endif // CELL_HPP

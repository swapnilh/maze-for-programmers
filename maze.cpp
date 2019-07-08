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
	return cell->UnlinkCell(dir);
}

bool Maze::Link (int row, int col, Direction dir) {
	Cell* cell = cells_[row][col];
	return cell->LinkCell(dir);
}

std::vector<Cell*> Maze::GetDeadendCells() {
	std::vector<Cell*> deadend_list;
	for (int row = 0; row < num_rows_; row++) {
		for (int col = 0; col < num_cols_; col++) {
			auto* cell = cells_[row][col];
			auto neighbors = cell->GetNeighbors();
			int links = 0;
			for (auto* neighbor : neighbors) {
				if (cell->Linked(neighbor))
					links++;
			}
			if (links == 1) {	
				deadend_list.push_back(cell);
			}
		}
	}
	return deadend_list;
}

void Maze::Reset () {
	for (int row = 0; row < num_rows_; row++) {
		for (int col = 0; col < num_cols_; col++) {
			auto* cell = cells_[row][col];
			cell->starred = false;
			if (!IsInvalid(row+1, col))
						cell->AddNeighbor(Direction::North, cells_[row+1][col]);
			if (!IsInvalid(row-1, col))
						cell->AddNeighbor(Direction::South, cells_[row-1][col]);
			if (!IsInvalid(row, col+1))
						cell->AddNeighbor(Direction::East, cells_[row][col+1]);
			if (!IsInvalid(row, col-1))
						cell->AddNeighbor(Direction::West, cells_[row][col-1]);
			cell->UnlinkCell(Direction::North);
			cell->UnlinkCell(Direction::East);
			cell->UnlinkCell(Direction::West);
			cell->UnlinkCell(Direction::South);
		}
	}
}

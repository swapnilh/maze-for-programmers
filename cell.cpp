#include <iostream>
#include <cassert>
#include "cell.hpp"

bool Cell::Linked (Cell* cell) {
	for (auto* linked_cell : links) {
		// TODO: check pointers or contents?
		if (cell == linked_cell)
			return true;
	}
	return false;
}

void Cell::LinkCell (Cell* cell) {
	// Already linked
	if (Linked(cell))
		return;
	links.push_back(cell);
	cell->LinkCell(this);
}

void Cell::UnlinkCell (Cell* cell) {
	for (auto it = links.begin(); it != links.end(); it++) {
		if (*it == cell) {
			links.erase(it);
			cell->UnlinkCell(this);
			break;
		}
	}
}

// We need both associative and iterative access to neighbors. 
Cell* Cell::GetNeighbor(Direction dir) {
	switch (dir) {
		case Direction::North:
			return north_cell;
			break;
		case Direction::East:
			return east_cell;
			break;
		case Direction::West:
			return west_cell;
			break;
		case Direction::South:
			return south_cell;
			break;
	}
	return nullptr;
}

std::vector<Cell*> Cell::GetNeighbors () {
	std::vector<Cell*> neighbor_list;
	neighbor_list.push_back(GetNeighbor(Direction::North));
	neighbor_list.push_back(GetNeighbor(Direction::East));
	neighbor_list.push_back(GetNeighbor(Direction::West));
	neighbor_list.push_back(GetNeighbor(Direction::South));
	return neighbor_list;
}

void Cell::PrintCell(bool print_neighbors) {
	std::cout << "CELL:: {" << row << "," << col << "}";
	if (print_neighbors) {
		std::cout << " N,E,W,S:";
		auto neighbors = GetNeighbors();
		for (auto* cell : neighbors)
			cell->PrintCell(false);
		std::cout << std::endl;
	}
}

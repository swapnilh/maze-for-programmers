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

bool Cell::LinkCell (Direction dir) {
	auto idx = neighbors.find(dir);
	
	// No such neighbor
	if (idx == neighbors.end()) {
		return false;
	}
	
	auto* cell = idx->second;	
	return LinkCell(cell);
}

bool Cell::UnlinkCell (Direction dir) {
	auto idx = neighbors.find(dir);
	
	// No such neighbor
	if (idx == neighbors.end()) {
		return false;
	}

	auto* cell = idx->second;	
	return UnlinkCell(cell);	
}

bool Cell::LinkCell (Cell* cell) {
	if (cell == nullptr)
	return false;

	// Already linked
	if (!Linked(cell)) {
		links.push_back(cell);
		cell->LinkCell(this);
	}
	return true;
}

bool Cell::UnlinkCell (Cell* cell) {
	if (cell == nullptr)
	return false;

	for (auto it = links.begin(); it != links.end(); it++) {
		if (*it == cell) {
			links.erase(it);
			cell->UnlinkCell(this);
			return true;
		}
	}
	return false;
}

bool Cell::AddNeighbor (Direction dir, Cell* cell) {
	if (neighbors.find(dir) != neighbors.end()) {
		return false;
	}
	neighbors[dir] = cell;
  cell->AddNeighbor(InvertDirection(dir), this);	
	return true;
}

bool Cell::DeleteNeighbor (Direction dir) {
	auto neighbor = neighbors.find(dir);
	if (neighbor == neighbors.end())	return false;
	neighbors.erase(neighbor);
  neighbor->second->DeleteNeighbor(InvertDirection(dir));	
	return true;
}

// We need both associative and iterative access to neighbors. 
Cell* Cell::GetNeighbor(Direction dir) {
	auto neighbor = neighbors.find(dir);
	if (neighbor == neighbors.end())	return nullptr;
	return neighbor->second;
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
		auto neighbor_list = GetNeighbors();
		for (auto* cell : neighbor_list) {
			if (cell != nullptr)
				cell->PrintCell(false);
		}
		std::cout << std::endl;
	}
}

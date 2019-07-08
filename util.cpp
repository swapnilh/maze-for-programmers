#include <iostream>
#include "util.hpp"

Direction IntToDirection (int num) {
	switch (num) {
		case 0: return Direction::North;
		case 1: return Direction::East;
		case 2: return Direction::West;
		case 3: return Direction::South;
		default: std::cerr << "Invalid Direction" << std::endl;
	}
	// Just to avoid  warnings: Control reaches end of function.
	return Direction::North;
}

Direction InvertDirection (Direction dir) {
	if (dir == Direction::North)
		return Direction::South;
	else if (dir == Direction::South)
		return Direction::North;
	else if (dir == Direction::East)
		return Direction::West;
	else
		return Direction::East;
}

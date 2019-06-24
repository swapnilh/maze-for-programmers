#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <random>
#include "maze.hpp"
	
class BinaryTreeCreator {
	Maze& maze_;
	std::mt19937 rng_;
	
public:
	BinaryTreeCreator (Maze& maze) : maze_(maze), rng_((std::random_device())())
	{
	}

	void Generate() {
		// Generates random integers from the set [1, 2].
    std::uniform_int_distribution<int> dist2(1,2);

		for (int row = 0; row < maze_.GetNumRows(); row++) {
			for (int col = 0; col < maze_.GetNumCols(); col++) {
				int rand_int = dist2(rng_);

				if (rand_int == 1) { // Open North Wall if possible, else East.
					if (!maze_.OpenWall(row, col, Direction::North)) 
						maze_.OpenWall(row, col, Direction::East);
				} else {
					if (!maze_.OpenWall(row, col, Direction::East)) 
						maze_.OpenWall(row, col, Direction::North);
				}
			}
		}
	}

};

#endif // BINARY_TREE_HPP

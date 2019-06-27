#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include "maze_generator.hpp"
	
class BinaryTreeGenerator: public MazeGenerator {
public:
	BinaryTreeGenerator (Maze& maze) : MazeGenerator(maze, "BinaryTree")
		{}

	void Generate() override {
		// Generates random integers from the set [1, 2].
    std::uniform_int_distribution<int> dist2(1,2);

		for (int row = 0; row < maze_.GetNumRows(); row++) {
			for (int col = 0; col < maze_.GetNumCols(); col++) {
				int rand_int = dist2(rng_);

				if (rand_int == 1) { // Open North Wall if possible, else East.
					if (!maze_.Link(row, col, Direction::North)) 
						maze_.Link(row, col, Direction::East);
				} else {
					if (!maze_.Link(row, col, Direction::East)) 
						maze_.Link(row, col, Direction::North);
				}
			}
		}
	}

};

#endif // BINARY_TREE_HPP

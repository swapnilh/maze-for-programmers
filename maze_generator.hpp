#ifndef MAZE_GENERATOR_HPP
#define MAZE_GENERATOR_HPP

#include <random>
#include "maze.hpp"
	
class MazeGenerator {
public:
	Maze& maze_;
	std::mt19937 rng_;
  std::string name_;
	
	MazeGenerator (Maze& maze, std::string name)
	 : maze_(maze), rng_((std::random_device())()), name_(name)
	{}

	const std::string& GetName() {
		return name_;
	}

	virtual void Generate() = 0;
};

#endif // MAZE_GENERATOR_HPP

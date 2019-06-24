#include <iostream>
#include "maze.hpp"

void Maze::Display() {
  for (int row = 0; row < num_rows_; row++) {
    for (int col = 0; col < num_cols_; col++) {
      char symbol = (cells_[row][col] == false) ? ' ' : '#';
      std::cout << symbol;
    }
    std::cout << std::endl;
  }
}

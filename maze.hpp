#ifndef MAZE_HPP
#define MAZE_HPP

#include<vector>

// The M x N maze is represented as 2M+1 x 2N+1 as walls are stored as cells.
// All odd indices are real cells, even indices are walls (open or closed).
class Maze {
  int num_rows_;
  int num_cols_;
  // true = closed, false = open.
  // odd indices cannot be closed as they are real cells. 
  // TODO: store only walls and not cells.
  std::vector<std::vector<bool> > cells_; 
  
public:
  Maze(int num_rows, int num_cols) :
    num_rows_(2*num_rows+1), num_cols_(2*num_cols+1),
    cells_(2*num_rows+1, std::vector<bool>(2*num_cols+1, false)) {

    // Closing all east-west walls.
    for (int row = 0; row < num_rows_; row+=2) {
      for (int col = 0; col < num_cols_; col++) {
        cells_[row][col] = true;
      }
    }
    // Closing all north-south walls.
    for (int col = 0; col < num_cols_; col+=2) {
      for (int row = 0; row < num_rows_; row++) {
        cells_[row][col] = true;
      }
    }

  }

  void Display();

};

#endif // MAZE_HPP

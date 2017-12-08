#ifndef GAME_H__
#define GAME_H__

#include <vector>

enum CellState {
    None,
    Cross,
    Zero
}

#define FIELD_SIZE 3

class TicTacToeGame {

public:
  CellState[FIELD_SIZE][FIELD_SIZE]
    field = { { None, None, None },
              { None, None, None },
              { None, None, None } };
   /*
    0 1 2
    3 4 5
    6 7 8
   */

  TicTacToeGame()
  {
  }

  bool isEmpty(int x, int y) {
    return field[x][y] == None;
  }

  CellState allEqual(int idx_a, int idx_b, int idx_c) {
      int a = field[idx_a / FIELD_SIZE][idx_a % FIELD_SIZE];
      int b = field[idx_b / FIELD_SIZE][idx_b % FIELD_SIZE];
      int c = field[idx_c / FIELD_SIZE][idx_c % FIELD_SIZE];
      if (a == b && b == c) {
        return a;
      }
      return None;
  }

  CellState checkWinner() {
    const int wins_count = 8;

    CellState wins[] = { allEqual(0,1,2),
                      allEqual(3,4,5),
                      allEqual(6,7,8),
                      allEqual(0,3,6),
                      allEqual(1,4,7),
                      allEqual(2,5,8),
                      allEqual(0,4,8),
                      allEqual(2,4,6) };
    for (int i = 0; i < wins_count; i++) {
      if (wins[i] != None) {
        return wins[i];
      }
    }
    return None;
  }

  bool setCell(int x, int y, CellState newState)
  {
    assert(0 < x && x < FIELD_SIZE);
    assert(0 < y && y < FIELD_SIZE);
    if (field[x][y] == None) {
      field[x][y] = newState;
      return true;
    }
    return false;
  }

  ~TicTacToeGame() {
  }


};


#endif // GAME_H__

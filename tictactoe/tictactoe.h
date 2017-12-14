#ifndef GAME_H__
#define GAME_H__

#include <vector>
#include <assert.h>

enum CellState {
    None = 0,
    Cross = 1,
    Zero = 2
};

#define FIELD_SIZE 9
#define FIELD_WIDTH 3

class TicTacToeGame {

  public:
    CellState field[FIELD_SIZE];
    /*
     0 1 2
     3 4 5
     6 7 8
    */

    TicTacToeGame() : field {
        None, None, None,
        None, None, None,
        None, None, None
    } {}


    CellState allEqual(int idx_a, int idx_b, int idx_c) {
        CellState a = field[idx_a ];
        CellState b = field[idx_b ];
        CellState c = field[idx_c ];

        if (a == b && b == c) {
            return a;
        }

        return None;
    }

    CellState checkWinner() {
        const int wins_count = 8;

        CellState wins[] = { allEqual(0, 1, 2),
                             allEqual(3, 4, 5),
                             allEqual(6, 7, 8),
                             allEqual(0, 3, 6),
                             allEqual(1, 4, 7),
                             allEqual(2, 5, 8),
                             allEqual(0, 4, 8),
                             allEqual(2, 4, 6)
                           };

        for (int i = 0; i < wins_count; i++) {
            if (wins[i] != None) {
                return wins[i];
            }
        }

        return None;
    }

    CellState get(int f) {
        assert(0 <= f && f < FIELD_SIZE);
        return this->field[f];
    }

    CellState opposeTo(CellState s) {

        if (s == Cross) {
            return Zero;
        }

        if  (s == Zero) {
            return Cross;
        }

        return None;
    }

    bool setCell(int f,  CellState newState) {
        assert(0 <= f && f < FIELD_SIZE);

        if (field[f] == None) {
            field[f] = newState;
            return true;
        }

        return false;
    }

    ~TicTacToeGame() {
    }


};


#endif // GAME_H__

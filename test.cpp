#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Block.h"
#include "BlockFall.h"
#include "GameController.h"
#include "Leaderboard.h"


using namespace std;

void print_2d_vector(vector<vector<int>> &vec) {
    for (auto &row : vec) {
        for (auto &col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

int main() {
    double score = 0;
    int total_number = 1;

    vector<vector<int>> expected_grid_1 = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                           {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
                                           {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0 }};

    BlockFall game("testsIO/grid.dat", "testsIO/original_tetriminos_.dat", false, "testsIO/leaderboard_tmp.txt", "alperen");
    GameController controller1;
    controller1.play(game, "testsIO/commands_move_1.dat");

    print_2d_vector(game.grid);
    printf("------------------\n");
    print_2d_vector(expected_grid_1);

    if (game.grid == expected_grid_1) {
        score += 1;
    }
    
    
    cout << score / (double) total_number << endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Block.h"


using namespace std;

void print2dMatrix(vector<vector<bool>> matrix) {
    for (auto row : matrix) {
        for (auto cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    std::vector<std::vector<bool>> matrix1 = {
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    };

    std::vector<std::vector<bool>> matrix2 = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0}
    };

    Block *block1 = new Block();
    block1->set_shape(matrix1);
    Block *block1r = block1->right_rotation;
    Block *block2 = new Block();
    block2->set_shape(matrix2);
    block1->set_next_block(block2);
    // cout << (*block1->next_block == *block1r->right_rotation->right_rotation->next_block) << endl;
    cout << (block1->next_block->next_block == nullptr) << endl;
    block1->delete_block_chain();
    return 0;
}

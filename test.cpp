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
    std::vector<std::vector<bool>> matrix = {
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    };

    Block block;
    block.set_shape(matrix);
    cout << (block == *block.right_rotation->right_rotation->right_rotation->left_rotation->left_rotation) << endl;
    return 0;
}

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
    };


    Block *block1 = new Block();
    block1->set_shape(matrix1);

    print2dMatrix(block1->shape);
    cout << endl;
    print2dMatrix(block1->right_rotation->shape);
    return 0;
}

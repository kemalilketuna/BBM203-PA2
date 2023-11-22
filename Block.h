#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:

    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * right_rotation = nullptr; // Pointer to the block's clockwise neighbor block (its right rotation)
    Block * left_rotation = nullptr; // Pointer to the block's counter-clockwise neighbor block (its left rotation)
    Block * next_block = nullptr; // Pointer to the next block to appear in the game

    bool operator==(const Block& other) const {
        if (this->shape == other.shape) {
            return true;
        }
        return false;
    }

    bool operator!=(const Block& other) const {
        if (this->shape != other.shape) {
            return true;
        }
        return false;
    }

    vector<vector<bool>> cw_90_rotation(vector<vector<bool>> & matrix) {
        int n = matrix.size();
        int m = matrix.at(0).size();
        vector<vector<bool>> rotated_matrix(m, vector<bool>(n));
        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {
                rotated_matrix.at(m - j - 1).at(i) = matrix.at(i).at(j);
            }
        }
        return rotated_matrix;
    }

    void set_shape(vector<vector<bool>> shape) {
        if (this->right_rotation != nullptr || this->left_rotation != nullptr) {
            throw "block is already initialized";
        }
        vector<vector<bool>> cw_90_rotation = this->cw_90_rotation(shape);
        if (shape == cw_90_rotation) {
            this->shape = shape;
            this->right_rotation = this;
            this->left_rotation = this;
        }else{
            vector<vector<bool>> cw_180_rotation = this->cw_90_rotation(cw_90_rotation);
            if (shape == cw_180_rotation) {
                this->shape = shape;
                Block * right = new Block();
                right->shape = cw_90_rotation;
                this->right_rotation = right;
                this->left_rotation = right;
                right->left_rotation = this;
                right->right_rotation = this;
            }else{
                vector<vector<bool>> cw_270_rotation = this->cw_90_rotation(cw_180_rotation); 
                this->shape = shape;
                Block * right = new Block();
                right->shape = cw_90_rotation;
                Block * forth = new Block();
                forth->shape = cw_180_rotation;
                Block * left = new Block();
                left->shape = cw_270_rotation;
                this-> right_rotation = right;
                right->right_rotation = forth;
                forth->right_rotation = left;
                left->right_rotation = this;
                this->left_rotation = left;
                left->left_rotation = forth;
                forth->left_rotation = right;
                right->left_rotation = this;
            }
        }
    }

    void set_next_block(Block * next) {
        if (this->next_block != nullptr) {
            throw "next block is already initialized";
        }
        this->next_block = next;
        if (this->right_rotation != nullptr) {
            if (this->right_rotation->next_block != next){
            this->right_rotation->set_next_block(next);
            }
        }else{
            throw "circular linked list is not created properly";
        }
    }

    void delete_one_block_chain() {
        Block * r1 = this->right_rotation;
        Block * r2 = r1->right_rotation;
        Block * r3 = r2->right_rotation;

        if (r1 != this && r1 != nullptr && r1 != r2 && r1 != r3){
            delete r1;
        }
        if (r2 != this && r2 != nullptr && r2 != r3){
            delete r2;
        }
        if (r3 != this && r3 != nullptr){
            delete r3;
        }
        delete this;
    }
};

#endif //PA2_BLOCK_H

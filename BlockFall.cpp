#include "BlockFall.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}


void BlockFall::read_blocks(const string &input_file) {
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
    
    // open the file
    ifstream file(input_file);
    string line;

    Block * last2 = nullptr;
    vector<vector<bool>> matrix;
    while (getline(file, line))
    {
        vector<bool> row;
        for (char c : line){
            if (c == '1'){
                row.push_back(1);
            }
            else if (c == '0'){
                row.push_back(0);
            }else if (c == ']'){
                matrix.push_back(row);
                row.clear();
                Block * block = new Block();
                block->set_shape(matrix);
                if(initial_block == nullptr){
                    initial_block = block;
                    active_rotation = block;
                }else{
                    last2 = active_rotation;
                    active_rotation->set_next_block(block);
                    active_rotation = block;
                }
                matrix.clear();
            }
        }
        if(!row.empty()){
            matrix.push_back(row);
        }
    }
    
    // close the file
    file.close();

    // // set power_up
    power_up = active_rotation->shape;
    
    last2->set_next_block(nullptr);
    active_rotation->delete_one_block_chain();

    // set initial  pointer to the first active rotation
    active_rotation = initial_block;


}

void BlockFall::initialize_grid(const string &input_file) {
    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
    ifstream file(input_file);
    string line;

    if(!grid.empty()){
        throw "grid is already initialized";
    }

    while (getline(file, line))
    {
        vector<int> row;
        for (char c : line){
            if (c == '1'){
                row.push_back(1);
            }
            else if (c == '0'){
                row.push_back(0);
            }
        }
        grid.push_back(row);
    }
    rows = grid.size();
    cols = grid.at(0).size();
    file.close();
}


BlockFall::~BlockFall() {
    // TODO: Free dynamically allocated memory used for storing game blocks
    while(initial_block != nullptr){
        Block * temp = initial_block;
        initial_block = initial_block->next_block;
        temp->delete_one_block_chain();
        
    }
}

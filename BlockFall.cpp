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
    cout << "reading blocks" << endl;
    ifstream file(input_file);
    string line;

    vector<vector<bool>> matrix;
    while (getline(file, line))
    {
        if (line[0] != '\r'){
            vector<bool> row;
            for (char c : line){
                if (c == '1'){
                    row.push_back(true);
                }
                else if (c == '0'){
                    row.push_back(false);
                }
            }
            matrix.push_back(row);
        }else{
            Block * block = new Block();
            block->set_shape(matrix);
            if (initial_block == nullptr){
                initial_block = block;
                active_rotation = block;
            }else{
                active_rotation->set_next_block(block);
            }
            //clear the matrix
            matrix.clear();
        }
    }

    power_up = active_rotation->next_block->shape;
    delete active_rotation->next_block;
    
    // close the file
    file.close();

    Block * temp = initial_block;
    while (temp != nullptr){
        cout << temp->shape.size() << 'x' << temp->shape.at(0).size() << endl;
        temp = temp->next_block;
    }
    cout << "initial block is null" << endl;
    
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
    //implement recursive delete function in block.h
    if (initial_block != nullptr){
        initial_block->delete_block();
    }
}

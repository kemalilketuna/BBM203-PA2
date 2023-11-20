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

    cout << static_cast<int>('\r') << 'test' << endl;
    vector<vector<bool>> matrix;
    while (getline(file, line))
    {
        for (char c : line)
        {
            cout << static_cast<int>(c) << " ";
        }
        cout << endl;
    }
    
    // close the file
    file.close();
}

void BlockFall::initialize_grid(const string &input_file) {
    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
}


BlockFall::~BlockFall() {
    // TODO: Free dynamically allocated memory used for storing game blocks
}

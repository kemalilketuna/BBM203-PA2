#ifndef PA2_GAMECONTROLLER_H
#define PA2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

class GameController {
public:
    bool play(BlockFall &game, const string &commands_file); // Function that implements the gameplay
private:
    int block_abscissa = 0; // Variable that stores the abscissa of the block
    int current_score = 0; // Variable that stores the current score
    bool executeCommands(BlockFall &game, const string &commands_file); // Function that executes a single command
    int athHighScore(BlockFall &game); // Function that returns the highest score
    void print_command(BlockFall &game); // Function that prints the grid
    void move_right(BlockFall &game); // Function that moves the block to the right
    void move_left(BlockFall &game); // Function that moves the block to the left
    void rotate_right(BlockFall &game); // Function that rotates the block to the right
    void rotate_left(BlockFall &game); // Function that rotates the block to the left
    void drop(BlockFall &game); // Function that drops the block
    int spawn_manager(BlockFall &game); // Function that spawns a new block
    void check_powerup(BlockFall &game); // Function that checks if a powerup is activated
    void print_before_clear(BlockFall &game); // Function that clears any filled rows
    void clear_rows(BlockFall &game); // Function that clears a filled row
    bool isSubMatrix(const vector<vector<int>>& bigMatrix, const vector<vector<bool>>& smallMatrix); // Function that checks if a submatrix is filled
    void switch_gravity(BlockFall &game); // Function that switches the gravity
    void print_no_more_blocks(BlockFall &game); // Function that prints the grid when there are no more blocks
    void print_no_more_commands(BlockFall &game); // Function that prints the grid when there are no more commands
    void print_game_over(BlockFall &game); // Function that prints the grid when the game is over
    void print_grid(BlockFall &game);   // Function that prints the grid
};


#endif //PA2_GAMECONTROLLER_H

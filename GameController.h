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
    void executeCommands(BlockFall &game, const string &commands_file); // Function that executes a single command
    int athHighScore(BlockFall &game); // Function that returns the highest score
    void print_command(BlockFall &game); // Function that prints the grid
    void move_right(BlockFall &game); // Function that moves the block to the right
    void move_left(BlockFall &game); // Function that moves the block to the left
    void drop(BlockFall &game); // Function that drops the block
};


#endif //PA2_GAMECONTROLLER_H

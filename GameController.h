#ifndef PA2_GAMECONTROLLER_H
#define PA2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

class GameController {
public:
    bool play(BlockFall &game, const string &commands_file); // Function that implements the gameplay
private:
    int current_score = 0;
    int athHighScore(BlockFall &game);
    void print_grid(BlockFall &game);
    void print_grid_and_score(BlockFall &game);
    void print_game_over(BlockFall &game);
    void print_no_more_commands(BlockFall &game);
    void print_no_more_blocks(BlockFall &game);
    void swith_gravity(BlockFall &game);
    void move_right(BlockFall &game);
    void move_left(BlockFall &game);
    void rotate_right(BlockFall &game);
    void rotate_left(BlockFall &game);
    void drop(BlockFall &game);
    void spawn_block(BlockFall &game);
};


#endif //PA2_GAMECONTROLLER_H

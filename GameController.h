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
    void print_game_over(BlockFall &game);
    void print_no_more_commands(BlockFall &game);
    void print_no_more_blocks(BlockFall &game);
    void switch_gravity(BlockFall &game);
    void print_command(BlockFall &game);
    void move_right(BlockFall &game);
    void move_left(BlockFall &game);
    void rotate_right(BlockFall &game);
    void rotate_left(BlockFall &game);
    void drop(BlockFall &game);
    bool spawn_manager(BlockFall &game);
    void clear_rows(BlockFall &game);
    void check_powerup(BlockFall &game);
    void print_before_clear(BlockFall &game);
    int block_abscissa = 0;
};


#endif //PA2_GAMECONTROLLER_H

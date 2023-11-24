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
};


#endif //PA2_GAMECONTROLLER_H

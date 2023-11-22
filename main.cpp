#include "BlockFall.h"
#include "GameController.h"
#include <iostream>

int main(int argc, char **argv) {
    // char * first = "samples/1_big_grid_gravity_switch/grid.dat";
    // char * second = "samples/1_big_grid_gravity_switch/blocks.dat";
    // char * third = "samples/1_big_grid_gravity_switch/commands.dat";
    // char * fourth = "GRAVITY_OFF";
    // char * fifth = "samples/leaderboard.txt";
    // char * sixth = "InfiniteLooper";

    // BlockFall game(first, second, false, fifth, sixth);
    // GameController controller;
    // controller.play(game, third);


    // // Create a BlockFall instance
    string gravity_mode(argv[4]);
    BlockFall game(argv[1], argv[2], (gravity_mode == "GRAVITY_ON"), argv[5], argv[6]);

    // Create a GameController instance
    GameController controller;

    // Play
    controller.play(game, argv[3]);

    return 0;
}
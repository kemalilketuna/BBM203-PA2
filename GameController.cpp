#include "GameController.h"
#include <iostream>
#include <fstream>

bool GameController::play(BlockFall& game, const string& commands_file){

    ifstream file(commands_file);
    std::string line;

    while (getline(file, line))
    {
        //PRINT_GRID
        if(line == "PRINT_GRID"){
            //do something
        }
        //ROTATE_RIGHT
        else if(line == "ROTATE_RIGHT"){
            //do something
        }
        //ROTATE_LEFT
        else if(line == "ROTATE_LEFT"){
            //do something
        }
        //MOVE_RIGHT
        else if(line == "MOVE_RIGHT"){
            //do something
        }
        //MOVE_LEFT
        else if(line == "MOVE_LEFT"){
            //do something
        }
        //GRAVITY_SWITCH
        else if(line == "GRAVITY_SWITCH"){
            //do something
        }
        //DROP
        else if(line == "DROP"){
            //do something
        }
    }

    return false;
}

int GameController::athHighScore(BlockFall &game){
    if(game.leaderboard.head_leaderboard_entry == nullptr){
        return this->current_score;
    }else if(game.leaderboard.head_leaderboard_entry->score < this->current_score){
        return this->current_score;
    }else{
        return game.leaderboard.head_leaderboard_entry->score;
    }
}

void GameController::print_grid(BlockFall &game){
    cout << "Score: " << this->current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;
    for(int i = 0; i < game.rows; i++){
        for(int j = 0; j < game.cols; j++){
            if(game.grid[i][j] == 1){
                cout << occupiedCellChar;
            }else{
                cout << unoccupiedCellChar;
            }
        }
        cout << endl;
    }
}



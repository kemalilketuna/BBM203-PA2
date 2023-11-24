#include "GameController.h"
#include <iostream>
#include <fstream>
#include <thread> // REMOVE IT LATER
#include <chrono> // REMOVE IT LATER

bool GameController::play(BlockFall& game, const string& commands_file){

    ifstream file(commands_file);
    std::string line;

    while (getline(file, line))
    {
        //PRINT_GRID
        if(line == "PRINT_GRID\r"){
            print_grid_and_score(game);
            cout << endl;
            cout << endl;
        }
        //ROTATE_RIGHT
        else if(line == "ROTATE_RIGHT\r"){
            //do something
        }
        //ROTATE_LEFT
        else if(line == "ROTATE_LEFT\r"){
            //do something
        }
        //MOVE_RIGHT
        else if(line == "MOVE_RIGHT\r"){
            //do something
        }
        //MOVE_LEFT
        else if(line == "MOVE_LEFT\r"){
            //do something
        }
        //GRAVITY_SWITCH
        else if(line == "GRAVITY_SWITCH\r"){
            //do something
        }
        //DROP
        else if(line == "DROP\r"){
            //do something
        }
        //REMOVE IT LATER
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return false;
}

void GameController::print_game_over(BlockFall &game){
    cout << "GAME OVER!" << endl;
    cout << "Next block that couldn't be fit:" << endl;
    game.active_rotation->print();
    cout << endl;
    cout << "Final grid and score:" << endl;
    cout << endl;
    print_grid_and_score(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::print_no_more_commands(BlockFall &game){
    cout << "GAME FINISHED!\n";
    cout << "No more comands.\n";
    cout << "Final grid and score:\n";
    cout << endl;
    print_grid_and_score(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::print_no_more_blocks(BlockFall &game){
    cout << "YOU WIN!\n";
    cout << "No more blocks.\n";
    cout << "Final grid and score:\n";
    cout << endl;
    print_grid_and_score(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::swith_gravity(BlockFall &game){}
void GameController::move_right(BlockFall &game){}
void GameController::move_left(BlockFall &game){}
void GameController::rotate_right(BlockFall &game){}
void GameController::rotate_left(BlockFall &game){}
void GameController::drop(BlockFall &game){}
void GameController::spawn_block(BlockFall &game){
    // if can spawn, spawn

    // else game over
    // check active rotation is correct
    print_grid_and_score(game);
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
    for(int i = 0; i < game.rows; i++){
        for(int j = 0; j < game.cols; j++){
            if(game.grid[i][j] == 1){
                cout << occupiedCellChar;
            }else{
                cout << unoccupiedCellChar;
            }
        }
        cout << "\n";
    }
}

void GameController::print_grid_and_score(BlockFall &game){
    cout << "Score: " << this->current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;
    print_grid(game);
}



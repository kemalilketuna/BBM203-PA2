#include "GameController.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread> // REMOVE IT LATER
#include <chrono> // REMOVE IT LATER

bool GameController::play(BlockFall& game, const string& commands_file){
    ifstream file(commands_file);
    std::string line;

    if (spawn_manager(game) == false) {
        return false;
    }

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
            swith_gravity(game);
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

void GameController::swith_gravity(BlockFall &game){
    // calculate a row how many ones
    int ones[game.cols];
    for (int row = 0; row < game.rows; row++) { // for each
        for (int col = 0; col < game.cols; col++) {
            if (game.grid[row][col] == 1) {
                ones[col] += 1;
            }
        }
    }

    // fill grid with ones bottom up
    for (int row = game.rows - 1; row >= 0; row--) { // for each
        for (int col = 0; col < game.cols; col++) {
            if (ones[col] > 0) {
                game.grid[row][col] = 1;
                ones[col] -= 1;
            } else {
                game.grid[row][col] = 0;
            }
        }
    }

    // clear filled rows
    clear_rows(game);

    // switch gravity
    game.gravity_mode_on = !game.gravity_mode_on;
}

void GameController::move_right(BlockFall &game){
    if (block_abscissa + game.active_rotation->width() < game.cols) {
        for (int row = 0; row < game.active_rotation->height(); row++) { // for each
            for (int col = 0; col < game.active_rotation->width(); col++) {
                if (game.active_rotation->shape[row][col] == 1) {
                    if (game.grid[row][col + 1] == 1) {
                        return;
                    }
                }
            }
        }
        block_abscissa += 1;
    }
}

void GameController::move_left(BlockFall &game){}
void GameController::rotate_right(BlockFall &game){}
void GameController::rotate_left(BlockFall &game){}
void GameController::drop(BlockFall &game){

    // update score
}

bool GameController::spawn_manager(BlockFall &game){
    if (game.active_rotation == nullptr) {
        print_no_more_blocks(game);
        return false;
    }

    // if can spawn, spawn
    for (int row = 0; row < game.active_rotation->height(); row++) { // for each
        for (int col = 0; col < game.active_rotation->width(); col++) {
            if (game.active_rotation->shape[row][col] == 1) {
                if (game.grid[row][col] == 1) {
                    print_game_over(game);
                    return false;
                }
            }
        }
    }
    block_abscissa = 0;
    game.active_rotation = game.active_rotation->next_block;
    return true;
}

void GameController::clear_rows(BlockFall &game){
    bool shouldClear = false;
    int rowCount = game.rows;
    for (int i = 0; i < rowCount; i++) {
        if (std::all_of(game.grid[i].begin(), game.grid[i].end(), [](int i) { return i == 1; })) {
            print_before_clear(game);
            shouldClear = true;
            break;
        }
    }
    if(shouldClear) {
        for (int i = 0; i < rowCount; i++) {
            game.grid.erase(game.grid.begin() + i);
            game.grid.insert(game.grid.begin(), vector<int>(game.cols, 0));
            game.current_score += game.cols; // increase score by number of columns
        }
    }
}

// !!!!!! CHECK THIS FUNCTION !!!!!!
void GameController::check_powerup(BlockFall &game){
    // check if powerup is activated
    if (std::all_of(game.power_up.begin(), game.power_up.end(), [](vector<bool> i) { return std::all_of(i.begin(), i.end(), [](bool j) { return j == 1; }); })) {
        print_before_clear(game);
        // increase score
        int cell = 0;
        for (int row = 0; row < game.rows; row++) { // for each
            cell += std::count(game.grid[row].begin(), game.grid[row].end(), 1);
        }
        game.current_score += cell + 1000;
        // clear grid
        for (int row = 0; row < game.rows; row++) { // for each
            game.grid[row].clear();
        }
    }
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
    int height = game.active_rotation->height();
    int width = game.active_rotation->width();
    vector<vector<bool>> shape = game.active_rotation->shape;
    for(int i = 0; i < game.rows; i++){
        for(int j = 0; j < game.cols; j++){
            if(game.grid[i][j] == 1){
                cout << occupiedCellChar;
            }else{
                if (i < height && block_abscissa <= j && j < width + block_abscissa && shape[i][j] == 1){
                    cout << occupiedCellChar;
                }else{
                    cout << unoccupiedCellChar;
                }
            }
        }
        cout << "\n";
    }
}

void GameController::print_before_clear(BlockFall &game){
    cout << "Before clear:\n";
    print_grid(game);
    cout << endl;
}

void GameController::print_grid_and_score(BlockFall &game){
    cout << "Score: " << this->current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;
    print_grid(game);
}



#include "GameController.h"
#include <iostream>
#include <fstream>
#include <algorithm>

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
            print_command(game);
            cout << endl;
            cout << endl;
        }
        //ROTATE_RIGHT
        else if(line == "ROTATE_RIGHT\r"){
            rotate_right(game);
        }
        //ROTATE_LEFT
        else if(line == "ROTATE_LEFT\r"){
            rotate_left(game);
        }
        //MOVE_RIGHT
        else if(line == "MOVE_RIGHT\r"){
            move_right(game);
        }
        //MOVE_LEFT
        else if(line == "MOVE_LEFT\r"){
            move_left(game);
        }
        //GRAVITY_SWITCH
        else if(line == "GRAVITY_SWITCH\r"){
            swith_gravity(game);
            
            // check if powerup is activated
            check_powerup(game);

            // clear filled rows
            clear_rows(game);
        }
        //DROP
        else if(line == "DROP\r"){
            drop(game);
    
            // check if powerup is activated
            check_powerup(game);

            // clear any filled rows
            clear_rows(game);

            // spawn new block
            if (spawn_manager(game) == false) {
                return false;
            }
        }
       
    }

    print_no_more_commands(game);
    cout << endl;
    cout << endl;
    return false;
}

void GameController::print_game_over(BlockFall &game){
    cout << "GAME OVER!" << endl;
    cout << "Next block that couldn't be fit:" << endl;
    game.active_rotation->print();
    cout << endl;
    cout << "Final grid and score:" << endl;
    cout << endl;
    for (int row = 0; row < game.rows; row++) { // for each
        for (int col = 0; col < game.cols; col++) {
            if (game.grid[row][col] == 1) {
                cout << occupiedCellChar;
            } else {
                cout << unoccupiedCellChar;
            }
        }
        cout << endl;
    }
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::print_no_more_commands(BlockFall &game){
    cout << "GAME FINISHED!\n";
    cout << "No more comands.\n";
    cout << "Final grid and score:\n";
    cout << endl;
    print_grid(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::print_no_more_blocks(BlockFall &game){
    cout << "YOU WIN!\n";
    cout << "No more blocks.\n";
    cout << "Final grid and score:\n";
    cout << endl;
    print_grid(game);
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

void GameController::move_left(BlockFall &game){
    if (block_abscissa > 0) {
        for (int row = 0; row < game.active_rotation->height(); row++) { // for each
            for (int col = 0; col < game.active_rotation->width(); col++) {
                if (game.active_rotation->shape[row][col] == 1) {
                    if (game.grid[row][col - 1] == 1) {
                        return;
                    }
                }
            }
        }
        block_abscissa -= 1;
    }
}

void GameController::rotate_right(BlockFall &game){
    Block * right_block = game.active_rotation->right_rotation;
    vector<vector<bool>> shape = right_block->shape;
    int height = right_block->height();
    int width = right_block->width();
    for (int row = 0; row < height; row++) { // for each
        for (int col = 0; col < width; col++) {
            if (shape[row][col] == 1) {
                if (game.grid[row][col + block_abscissa] == 1) {
                    return;
                }
            }
        }
    }
    game.active_rotation = game.active_rotation->right_rotation;
}

void GameController::rotate_left(BlockFall &game){
    vector<vector<bool>> shape = game.active_rotation->left_rotation->shape;
    int height = game.active_rotation->left_rotation->height();
    int width = game.active_rotation->left_rotation->width();
    for (int row = 0; row < height; row++) { // for each
        for (int col = 0; col < width; col++) {
            if (shape[row][col] == 1) {
                if (game.grid[row][col + block_abscissa] == 1) {
                    return;
                }
            }
        }
    }
    game.active_rotation = game.active_rotation->left_rotation;
}

void GameController::drop(BlockFall &game){
    Block * block = game.active_rotation;
    int block_height = block->height();
    int block_width = block->width();
    
    if(!game.gravity_mode_on){
        // move block down until it can't move down anymore

        
        // find upper limit of grid
        int grid_limit[block_width] = {0};
        
        for(int col = 0; col < block_width; col++){
            for (int row = 0; row < game.rows; row++){
                if (game.grid[row][col+block_abscissa] == 1){
                    grid_limit[col] = row;
                    break;
                }
                grid_limit[col] = game.rows;
            }
        }

        // find bottom limit of block
        int block_limit[block_width] = {0};
        
        for(int col = 0; col < block_width; col++){
            for(int row = block_height - 1; row >= 0; row--){
                if(block->shape[row][col] == 1){
                    block_limit[col] = row;
                    break;
                }
            }
        }
        
        int shift = 0;
        if (block_height > 0 && block_width > 0){
            shift = grid_limit[0] - block_limit[0] - 1;
        }
        
        // find the smallest shift
        for(int i = 1; i < block_width; i++){
            int temp = grid_limit[i] - block_limit[i] - 1;
            if(temp < shift){
                shift = temp;
            }
        }

        // move block down by shift
        for(int row = block_height - 1; row >= 0; row--){
            for(int col = 0; col < block_width; col++){
                if(block->shape[row][col] == 1){
                    game.grid[row + shift][col + block_abscissa] = 1;
                }
            }
        }

        game.current_score += shift * block->ocuppied_cell_count();

    }else{
        /*
        // gravity mode on
        int bottom_limit[width];
        for (int col = 0; col < width; col++){
            for (int row = 0; row < game.rows; row++){
                if (game.active_rotation->shape[row][col+block_abscissa] == 1){
                    if(bottom_limit[col] == 0){
                        bottom_limit[col] = row;
                    }
                }
            }
        }

        for (int row = height - 1; row >= 0; row--){
            for (int col = 0; col < width; col++){
                if (game.active_rotation->shape[row][col] == 1){
                    current_score += bottom_limit[col] - row;
                    bottom_limit[col] -= 1;
                    game.grid[bottom_limit[col]-1][col + block_abscissa] = 1; 
                }
            } 
        }
        */
    }
}

bool GameController::spawn_manager(BlockFall &game){
    if (game.active_rotation == nullptr) {
        print_no_more_blocks(game);
        return false;
    }

    block_abscissa = 0;
    if (game.current_score > 0){
        game.active_rotation = game.active_rotation->next_block;
        if (game.active_rotation == nullptr) {
            print_no_more_blocks(game);
            return false;
        }
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

void GameController::print_grid_and_block(BlockFall &game){
    int height = game.active_rotation->height();
    int width = game.active_rotation->width();
    vector<vector<bool>> shape = game.active_rotation->shape;
    for(int i = 0; i < game.rows; i++){
        for(int j = 0; j < game.cols; j++){
            if(game.grid[i][j] == 1){
                cout << occupiedCellChar;
            }else{
                int shape_col = j - block_abscissa;
                if (
                    i >= 0 && i < height &&
                    shape_col >= 0 && shape_col < width &&
                    shape[i][shape_col] == 1
                ){
                    cout << occupiedCellChar;
                }else{
                    cout << unoccupiedCellChar;
                }
            }
        }
        cout << "\n";
    }
}

void GameController::print_grid(BlockFall &game){
    int height = game.active_rotation->height();
    int width = game.active_rotation->width();
    for (int row = 0; row < game.rows; row++) { // for each
        for (int col = 0; col < game.cols; col++) {
            if (game.grid[row][col] == 1) {
                cout << occupiedCellChar;
            } else {
                cout << unoccupiedCellChar;
            }
        }
        cout << endl;
    }
}

void GameController::print_before_clear(BlockFall &game){
    cout << "Before clear:\n";
    print_grid(game);
    cout << endl;
}

void GameController::print_command(BlockFall &game){
    cout << "Score: " << this->current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;
    print_grid_and_block(game);
}



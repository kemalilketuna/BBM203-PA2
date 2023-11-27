#include "GameController.h"
#include "iostream"
#include <fstream>
#include <algorithm>

bool GameController::play(BlockFall& game, const string& commands_file){
    executeCommands(game, commands_file);
    return false;
}

void GameController::executeCommands(BlockFall& game, const string& commands_file){
    ifstream file(commands_file);
    std::string line;

    while (getline(file, line))
    {
        //PRINT_GRID
        if(line == "PRINT_GRID\r"){
            print_command(game);
        }
        //ROTATE_RIGHT
        else if(line == "ROTATE_RIGHT\r"){
            cout << "ROTATE_RIGHT" << endl;
        }
        //ROTATE_LEFT
        else if(line == "ROTATE_LEFT\r"){
            cout << "ROTATE_LEFT" << endl;
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
            cout << "GRAVITY_SWITCH" << endl;
        }
        //DROP
        else if(line == "DROP\r"){
            drop(game);
        }
       
    }
}

// Move Functions
//----------------------------------------------
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

//----------------------------------------------



// Drop Function
//----------------------------------------------
void GameController::drop(BlockFall &game){
    Block * block = game.active_rotation;
    int block_height = block->height();
    int block_width = block->width();
    
    
    // find upper limit of grid
    int grid_limit[block_width] = {0};

    for(int col = 0; col < block_width; col++){
        grid_limit[col] = game.rows;
        for (int row = 0; row < game.rows; row++){
            if (game.grid[row][col+block_abscissa] == 1){
                grid_limit[col] = row;
                break;
            }
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
                if(!game.gravity_mode_on){
                    game.grid[row + shift][col + block_abscissa] = 1;
                }
            }
        }
    }
    game.current_score += shift * block->occupied_cell_count();

    if(game.gravity_mode_on){
        int grid_limit[block_width] = {0};
        for (int col = 0; col < block_width; col++){
            grid_limit[col] = game.rows;
        
            for (int row = 0; row < game.rows; row++){
                if (game.grid[row][col+block_abscissa] == 1){
                    grid_limit[col] = row;
                    break;
                }
            } 
        }
        for (int row = block_height - 1; row >= 0; row--){
            for (int col = 0; col < block_width; col++){
                if (game.active_rotation->shape[row][col] == 1){
                    current_score += grid_limit[col] - row;
                    grid_limit[col] -= 1;
                    game.grid[grid_limit[col]][col + block_abscissa] = 1; 
                }
            } 
        }
    }
}

//----------------------------------------------

int GameController::athHighScore(BlockFall &game){
    if(game.leaderboard.head_leaderboard_entry == nullptr){
        return game.current_score;
    }else if(game.leaderboard.head_leaderboard_entry->score < game.current_score){
        return game.current_score;
    }else{
        return game.leaderboard.head_leaderboard_entry->score;
    }
}

void GameController::print_command(BlockFall &game){
    cout << "Score: " << game.current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;
    
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

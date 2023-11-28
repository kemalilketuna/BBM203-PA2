#include "GameController.h"
#include "iostream"
#include <fstream>
#include <algorithm>

using namespace std;

bool GameController::play(BlockFall& game, const string& commands_file){
    return executeCommands(game, commands_file);
}

bool GameController::executeCommands(BlockFall& game, const string& commands_file){
    ifstream file(commands_file);
    std::string line;
    
    int status = spawn_manager(game);
    if (status == 1) {
        print_no_more_blocks(game);
        return true;
    } else if (status == 2) {
        print_game_over(game);
        return false;
    }

    while (getline(file, line))
    {
        //PRINT_GRID
        if(line.substr(0, 10) == "PRINT_GRID"){
            print_command(game);
            cout << endl;
            cout << endl;
        }
        //ROTATE_RIGHT
        else if(line.substr(0, 12) == "ROTATE_RIGHT"){
            rotate_right(game);
        }
        //ROTATE_LEFT
        else if(line.substr(0, 11) == "ROTATE_LEFT"){
            rotate_left(game);
        }
        //MOVE_RIGHT
        else if(line.substr(0, 10) == "MOVE_RIGHT"){
            move_right(game);
        }
        //MOVE_LEFT
        else if(line.substr(0, 9) == "MOVE_LEFT"){
            move_left(game);
        }
        //GRAVITY_SWITCH
        else if(line.substr(0, 15) == "GRAVITY_SWITCH"){
            switch_gravity(game);

            check_powerup(game);

            clear_rows(game);
        }
        //DROP
        else if(line.substr(0, 4) == "DROP"){
            drop(game);
    
            // check if powerup is activated
            check_powerup(game);

            // clear any filled rows
            clear_rows(game);

            // spawn new block
            int status = spawn_manager(game);
            if (status == 1) {
                print_no_more_blocks(game);
                return true;
            } else if (status == 2) {
                print_game_over(game);
                return false;
            }
        }
    }
    print_no_more_commands(game);
    cout << endl;
    cout << endl;
    return true;
}

// Move Functions
//----------------------------------------------
void GameController::move_right(BlockFall &game){
    if (block_abscissa + game.active_rotation->width() < game.cols) {
        for (int row = 0; row < game.active_rotation->height(); row++) { // for each
            for (int col = 0; col < game.active_rotation->width(); col++) {
                if (game.active_rotation->shape[row][col] == 1) {
                    if (game.grid[row][block_abscissa + col + 1] == 1) {
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
                    if (game.grid[row][block_abscissa + col - 1] == 1) {
                        return;
                    }
                }
            }
        }
        block_abscissa -= 1;
    }
}
//----------------------------------------------

// Rotate Functions
//----------------------------------------------
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

void GameController::clear_rows(BlockFall &game){
    bool shouldPrint = true;
    int rowCount = game.rows;
    for (int i = 0; i < rowCount; i++) {
        if (std::all_of(game.grid[i].begin(), game.grid[i].end(), [](int i) { return i == 1; })) {
            if(shouldPrint) {
                print_before_clear(game);
                shouldPrint = false;
            }
            game.grid.erase(game.grid.begin() + i);
            game.grid.insert(game.grid.begin(), vector<int>(game.cols, 0));
            game.current_score += game.cols; // increase score by number of columns
        }
    }

}

int GameController::spawn_manager(BlockFall &game){
    if (game.active_rotation == nullptr) {
        // print_no_more_blocks(game);
        return 1;
    }

    block_abscissa = 0;
    if (game.current_score > 0){
        game.active_rotation = game.active_rotation->next_block;
        if (game.active_rotation == nullptr) {
            print_no_more_blocks(game);
            return 1;
        }
    }

    // if can spawn, spawn
    for (int row = 0; row < game.active_rotation->height(); row++) { // for each
        for (int col = 0; col < game.active_rotation->width(); col++) {
            if (game.active_rotation->shape[row][col] == 1) {
                if (game.grid[row][col] == 1) {
                    // record_score(game);
                    print_game_over(game);
                    return 2;
                }
            }
        }
    }
    return 0;
}

// Print Functions
//----------------------------------------------

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


void GameController::print_before_clear(BlockFall &game){
    cout << "Before clearing:\n";
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
    cout << endl;
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

void GameController::print_no_more_commands(BlockFall &game){
    cout << "GAME FINISHED!\n";
    cout << "No more comands.\n";
    cout << "Final grid and score:\n";
    cout << endl;
    print_grid(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}


void GameController::print_game_over(BlockFall &game){
    cout << "GAME OVER!" << endl;
    cout << "Next block that couldn't be fit:" << endl;
    game.active_rotation->print();
    cout << endl;
    cout << "Final grid and score:" << endl;
    cout << endl;
    print_grid(game);
    cout << endl;
    game.leaderboard.print_leaderboard();
}

void GameController::print_grid(BlockFall &game){
    cout << "Score: " << game.current_score << endl;
    cout << "High Score: " << athHighScore(game) << endl;

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

int GameController::athHighScore(BlockFall &game){
    if(game.leaderboard.head_leaderboard_entry == nullptr){
        return game.current_score;
    }else if(game.leaderboard.head_leaderboard_entry->score < game.current_score){
        return game.current_score;
    }else{
        return game.leaderboard.head_leaderboard_entry->score;
    }
}

//----------------------------------------------

// Gravity Function
//----------------------------------------------
void GameController::switch_gravity(BlockFall &game){
    // calculate a row how many ones
    int ones[game.cols] = {0};
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
//----------------------------------------------

// Powerup Functions
//----------------------------------------------
void GameController::check_powerup(BlockFall &game){
    // check if powerup is activated
    if (isSubMatrix(game.grid, game.power_up)) {
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

bool GameController::isSubMatrix(const vector<vector<int>>& bigMatrix, const vector<vector<bool>>& smallMatrix) {
    int bigRows = bigMatrix.size();
    int bigCols = bigMatrix[0].size();
    int smallRows = smallMatrix.size();
    int smallCols = smallMatrix[0].size();

    for (int i = 0; i <= bigRows - smallRows; ++i) {
        for (int j = 0; j <= bigCols - smallCols; ++j) {
            bool match = true;

            for (int x = 0; x < smallRows; ++x) {
                for (int y = 0; y < smallCols; ++y) {
                    if (bigMatrix[i + x][j + y] != smallMatrix[x][y]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }

            if (match) return true;
        }
    }
    return false;
}
// ----------------------------------------------
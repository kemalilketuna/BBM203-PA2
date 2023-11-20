#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

void read_blocks(const string &input_file) {
    ifstream file(input_file);
    string line;

    cout << static_cast<int>('\r') <<endl;
    vector<vector<bool>> matrix;
    while (getline(file, line))
    {
        for (char c : line)
        {
            cout << static_cast<int>(c) << " ";
        }
        cout << endl;
    }
    
    // close the file
    file.close();
}

int main() {
    string filename = "C:\\Users\\kemal\\Documents\\203 assignments\\assignment 2\\sampleIO\\1_big_grid_gravity_switch\\blocks.dat"; // Replace with your file's name and path
    read_blocks(filename);
    return 0;
}

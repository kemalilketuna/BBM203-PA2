#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include <iomanip>



// Insert a new entry
void Leaderboard::insert_new_entry(LeaderboardEntry* new_entry) {
    // If no head, set new entry as head
    if (head_leaderboard_entry == nullptr){
        head_leaderboard_entry = new_entry;
    }
    // If the leaderboard is empty or the new entry has a higher score than the head 
    else if (new_entry->score > head_leaderboard_entry->score) {
        new_entry->next_leaderboard_entry = head_leaderboard_entry;
        head_leaderboard_entry = new_entry;
    }
    else {
        LeaderboardEntry* current = head_leaderboard_entry;
        // Find the position to insert the new entry
        while (current->next_leaderboard_entry && current->next_leaderboard_entry->score >= new_entry->score) {
            current = current->next_leaderboard_entry;
        }
        new_entry->next_leaderboard_entry = current->next_leaderboard_entry;
        current->next_leaderboard_entry = new_entry;
    }

    // Trimming the leaderboard
    LeaderboardEntry* current = head_leaderboard_entry;
    int count = 1;
    while (current->next_leaderboard_entry && count < MAX_LEADERBOARD_SIZE) {
        count++;
        current = current->next_leaderboard_entry;
        if (count == MAX_LEADERBOARD_SIZE) {
            LeaderboardEntry * temp = current->next_leaderboard_entry;
            current->next_leaderboard_entry = nullptr;
            while (temp) {
                LeaderboardEntry * next = temp->next_leaderboard_entry;
                delete temp;
                temp = next;
            }
            break;
        }
    }
}

void Leaderboard::write_to_file(const string& filename) {
    std::ofstream file(filename);
    // if (!file.is_open()) {
    //     throw std::runtime_error(filename + " could not be opened for writing.");
    // }

    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        // Write to file
        file << current->score << " " << current->last_played << " " << current->player_name << endl;
        current = current->next_leaderboard_entry;
    }

    file.close();
}


void Leaderboard::read_from_file(const string& filename) {
    std::ifstream file(filename);
    // if (!file.is_open()) {
    //    throw std::runtime_error(filename + " could not be opened for reading.");
    // }

    unsigned long score;
    time_t lastPlayed;
    string playerName;
    
    // Read from file
    while (file >> score >> lastPlayed >> playerName) {
        LeaderboardEntry* newEntry = new LeaderboardEntry(score, lastPlayed, playerName);
        insert_new_entry(newEntry);
    }
    file.close();
}

// Print the leaderboard
void Leaderboard::print_leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    int rank = 0;

    std::cout << "Leaderboard\n";
    std::cout << "-----------\n";

    while (current != nullptr) {
        rank++;
        std::cout << rank << ". "; //print rank
        std::cout << current->player_name << " "; //print name
        std::cout << current->score << " "; // print score
        // prin time and flash buffer
        std::cout << std::put_time(std::localtime(&current->last_played), "%H:%M:%S/%d.%m.%Y") << std::endl;
        current = current->next_leaderboard_entry;
    }
}

// Destructor
Leaderboard::~Leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    while (current) {
        LeaderboardEntry* next = current->next_leaderboard_entry;
        delete current;
        current = next;
    }
}

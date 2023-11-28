#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include <iomanip>

// Destructor
Leaderboard::~Leaderboard() {
    while (head_leaderboard_entry != nullptr) {
        LeaderboardEntry* temp = head_leaderboard_entry;
        head_leaderboard_entry = head_leaderboard_entry->next_leaderboard_entry;
        delete temp;
    }
}

// Insert a new entry
void Leaderboard::insert_new_entry(LeaderboardEntry* new_entry) {
    if (!head_leaderboard_entry || new_entry->score > head_leaderboard_entry->score) {
        new_entry->next_leaderboard_entry = head_leaderboard_entry;
        head_leaderboard_entry = new_entry;
    } else {
        LeaderboardEntry* current = head_leaderboard_entry;
        while (current->next_leaderboard_entry && current->next_leaderboard_entry->score >= new_entry->score) {
            current = current->next_leaderboard_entry;
        }
        new_entry->next_leaderboard_entry = current->next_leaderboard_entry;
        current->next_leaderboard_entry = new_entry;
    }

    // Trimming the leaderboard
    LeaderboardEntry* temp = head_leaderboard_entry;
    int count = 1;
    while (temp && temp->next_leaderboard_entry && count < MAX_LEADERBOARD_SIZE) {
        temp = temp->next_leaderboard_entry;
        count++;
    }

    if (temp->next_leaderboard_entry) {
        LeaderboardEntry* excess = temp->next_leaderboard_entry;
        temp->next_leaderboard_entry = nullptr;
        while (excess) {
            LeaderboardEntry* next = excess->next_leaderboard_entry;
            delete excess;
            excess = next;
        }
    }
}

// Write to file
void Leaderboard::write_to_file(const string& filename) {
    std::ofstream file(filename);
    // if (!file.is_open()) {
    //     std::cerr << "Failed to open file for writing: " << filename << std::endl;
    //     return;
    // }

    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        file << current->score << " " << current->last_played << " " << current->player_name << "\n";
        current = current->next_leaderboard_entry;
    }

    file.close();
}

// Read from file
void Leaderboard::read_from_file(const string& filename) {
    std::ifstream file(filename);
    // if (!file.is_open()) {
    //     std::cerr << "Failed to open file for reading: " << filename << std::endl;
    //     return;
    // }

    unsigned long score;
    time_t lastPlayed;
    string playerName;

    while (file >> score >> lastPlayed >> playerName) {
        LeaderboardEntry* newEntry = new LeaderboardEntry(score, lastPlayed, playerName);
        insert_new_entry(newEntry);
    }

    file.close();
}

// Print the leaderboard
void Leaderboard::print_leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    int rank = 1;

    std::cout << "Leaderboard\n-----------\n";
    while (current != nullptr) {
        std::cout << rank << ". " << current->player_name << " " << current->score << " ";
        std::cout << std::put_time(std::localtime(&current->last_played), "%H:%M:%S/%d.%m.%Y") << std::endl;
        current = current->next_leaderboard_entry;
        rank++;
    }
}

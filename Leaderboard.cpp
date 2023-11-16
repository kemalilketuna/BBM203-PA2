#include "Leaderboard.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

void Leaderboard::insert_new_entry(LeaderboardEntry* new_entry) {
    // Check if the new entry is valid
    if (new_entry == nullptr) {
        std::cerr << "Invalid new entry." << std::endl;
        return;
    }

    // Handle the case where the leaderboard is empty
    if (head_leaderboard_entry == nullptr) {
        head_leaderboard_entry = new_entry;
        return;
    }

    // Inserting in a non-empty list
    LeaderboardEntry* current = head_leaderboard_entry;
    LeaderboardEntry* previous = nullptr;

    while (current != nullptr && current->score > new_entry->score) {
        previous = current;
        current = current->next_leaderboard_entry;
    }

    // Insert new_entry before the current node
    if (previous != nullptr) { // Inserting somewhere after the head
        previous->next_leaderboard_entry = new_entry;
    } else { // Inserting at the head
        head_leaderboard_entry = new_entry;
    }
    new_entry->next_leaderboard_entry = current;

    // Ensure leaderboard size does not exceed 10
    current = head_leaderboard_entry;
    int count = 1;
    while (current != nullptr && count < 10) {
        previous = current;
        current = current->next_leaderboard_entry;
        count++;
    }

    // If the leaderboard has more than 10 entries, trim the last one
    if (current != nullptr) {
        previous->next_leaderboard_entry = nullptr;
        // Delete the extra entry if you are managing memory, e.g., delete current;
    }
}


void Leaderboard::write_to_file(const string& filename) {
    // 1. Open the file
    std::ofstream file(filename);
    LeaderboardEntry* current = head_leaderboard_entry;

    while (current != nullptr) {
        // 2. Write the leaderboard entry to the file
        file << current->score << ' ' << current->last_played << ' ' << current->player_name << '\n';
        current = current->next_leaderboard_entry;
    }    
}

void Leaderboard::read_from_file(const string& filename) {
    std::ifstream file(filename);
    std::string line;

    // Read each line and create LeaderboardEntry objects
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        unsigned long score;
        time_t lastPlayed;
        std::string playerName;

        if (iss >> score >> lastPlayed >> playerName) {
            LeaderboardEntry newEntry = LeaderboardEntry(score, lastPlayed, playerName);
            insert_new_entry(&newEntry);
        }
    }

    // Close the file
    file.close();
}

void Leaderboard::print_leaderboard() {
    std::cout << "Leaderboard\n-----------\n";

    LeaderboardEntry* current = head_leaderboard_entry;
    int rank = 1;

    while (current != nullptr) {
        // Convert last played time from time_t to tm struct in UTC+3
        std::tm *ptm = std::gmtime(&current->last_played);
        ptm->tm_hour += 3; // Adjust for UTC+3

        // Handle potential day change due to time adjustment
        std::mktime(ptm);
        
        // rank - name - score - last played
        // 1. BlockBuster 40000 20:50:55/21.10.2023

        // Print the leaderboard entry
        std::cout << rank << '.' << ' ' << current->player_name << ' ' << current->score << ' '
                  << ptm->tm_hour << ':' << ptm->tm_min << ':' << ptm->tm_sec << '/'
                  << ptm->tm_mday << '.' << ptm->tm_mon + 1 << '.' << ptm->tm_year + 1900 << '\n';

        current = current->next_leaderboard_entry;
        ++rank;
    }
}

Leaderboard::~Leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    while (current != nullptr) {
        LeaderboardEntry* next = current->next_leaderboard_entry;
        delete current;
        current = next;
    }
}

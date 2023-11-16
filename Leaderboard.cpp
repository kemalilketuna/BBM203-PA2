#include "Leaderboard.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    // TODO: Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
    //       is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
    //       top 10 all-time high-scores should be kept in descending order by the score).
}

void Leaderboard::write_to_file(const string& filename) {
    // TODO: Write the latest leaderboard status to the given file in the format specified in the PA instructions
}

void Leaderboard::read_from_file(const string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<LeaderboardEntry*> entries;

    // Read each line and create LeaderboardEntry objects
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        unsigned long score;
        time_t lastPlayed;
        std::string playerName;

        if (iss >> score >> lastPlayed >> playerName) {
            entries.push_back(new LeaderboardEntry(score, lastPlayed, playerName));
        }
    }

    // Sort the entries in descending order of score
    std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry* a, const LeaderboardEntry* b) {
        return a->score > b->score;
    });

    // Link the entries
    for (size_t i = 0; i < entries.size(); ++i) {
        entries[i]->next_leaderboard_entry = (i + 1 < entries.size()) ? entries[i + 1] : nullptr;
    }

    // Set the head_leaderboard_entry to point to the entry with the highest score
    head_leaderboard_entry = entries.empty() ? nullptr : entries.front();

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
        // 2. StackOverthrower 1200 20:50:55/21.10.2023


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

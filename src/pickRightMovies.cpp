#include "pickRightMovies.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int PickRightFilms(const std::string &filename, std::vector<std::tuple<std::string, float>> &topTitles,
                   unsigned maxMinutes, std::vector<std::string> &rightMovies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error in open basics filename" << std::endl;
        return -1;
    }

    std::string first_line;
    getline(file, first_line);

    std::vector<std::tuple<std::string, float>> rightMoviesWithRating;

    while (!file.eof()) {
        std::string titleID;
        if (!ReadTitleBasicsFromFile(file, maxMinutes, titleID)) {
            continue;
        }

        // checking presence this title in top
        for (const auto &topTitle : topTitles) {
            if (std::get<0>(topTitle) == titleID) {
                rightMoviesWithRating.push_back(topTitle);
                break;
            }
        }
    }

    // sort, bsc we need top-10 (TOP_AMOUNT) rating
    std::sort(begin(rightMoviesWithRating), end(rightMoviesWithRating),
              [](auto const &t1, auto const &t2) { return std::get<1>(t1) > std::get<1>(t2); });

    for (unsigned i = rightMovies.size(); i < rightMoviesWithRating.size() && i < TOP_AMOUNT; ++i) {
        rightMovies.push_back(std::get<0>(rightMoviesWithRating[i]));
    }

    file.close();
    return 0;
}

bool ReadTitleBasicsFromFile(std::ifstream &file, unsigned maxMinutes, std::string &titleID) {
    std::string titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres;

    getline(file, titleID, '\t');
    getline(file, titleType, '\t');
    getline(file, primaryTitle, '\t');
    getline(file, originalTitle, '\t');
    getline(file, isAdult, '\t');
    getline(file, startYear, '\t');
    getline(file, endYear, '\t');
    getline(file, runtimeMinutes, '\t');
    getline(file, genres);

    // help not get error
    if (titleID.empty()) {
        return false;
    }

    if (titleID == "\\N" || titleType == "\\N" || isAdult == "\\N" || runtimeMinutes == "\\N") {
        return false;
    }

    if (std::stoi(runtimeMinutes) > maxMinutes || std::stoi(isAdult) || titleType != "movie") {
        return false;
    }
    return true;
}

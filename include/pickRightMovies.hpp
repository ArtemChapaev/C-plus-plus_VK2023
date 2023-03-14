#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "printMovieNames.hpp"

int PickRightFilms(const std::string &filename, std::vector<std::tuple<std::string, float>> &topTitles,
                   unsigned maxMinutes, std::vector<std::string> &rightMovies);
/// Parameters filename with ratings, full vector of top pair "titleID-averageRating",
/// maxMinutes from argv, not full vector of top movies. Return values - 0 or error
/// Create top movies with needed parameters.
/// Read from file and select needed movies. Search movie's ID in topTitles.

bool ReadTitleBasicsFromFile(std::ifstream &file, unsigned maxMinutes, std::string &titleID);
/// Parameters - ifstream for reading, maxMinutes from argv, string for writing titleID.
/// Return values - true if task's conditions are complete.
/// Read title from file and if it is right return titleID.

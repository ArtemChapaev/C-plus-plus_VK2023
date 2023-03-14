#pragma once

#include <string>
#include <tuple>
#include <vector>

const int TOP_AMOUNT = 10;

int PrintMovieNames(std::string &filename, std::vector<std::string> &topMovies);
/// Parameters - filename with "akas", full vector with picked top movies.
/// Return values - 0 or error.
/// Read from file all "akas", for each "aka" compare title ID with titleID from topMovies.
/// Finally for every topMovie will be printed ru-name or primary name.

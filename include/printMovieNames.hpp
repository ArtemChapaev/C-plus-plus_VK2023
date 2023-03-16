#pragma once

#include <string>
#include <vector>

namespace TopFilmSelection {

struct MovieName {
    std::string name;
    bool wasRuName;
    bool wasOriginalName;
};
/// first flag show priority of ru-name, second - priority of original name.

void PrintMovieNames(std::string &filename, std::vector<std::string> &topMovies);
/// Parameters - filename with "akas", full vector with picked top movies.
/// Read from file all "akas", for each "aka" compare ID with movieID from topMovies.
/// Finally for every topMovie will be printed ru-name or primary name.

}  // namespace TopFilmSelection

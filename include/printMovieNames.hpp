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

struct AkasInfo {
    std::string titleID;
    std::string title;
    std::string region;
    std::string language;
    std::string isOriginalTitle;
};

void PrintMovieNames(std::string &filename, std::vector<std::string> &topMovies);
/// Parameters - filename with "akas", full vector with picked top movies.
/// Read from file all "akas", for each "aka" use FindMovieName.
/// Finally for every topMovie will be printed ru-name or primary name.

void FindMovieName(std::vector<std::string> &topMovies, std::vector<MovieName> &movieNames,
                   AkasInfo titleInfo);
/// Parameters - vector with picked top movies, vector for writing of movie's name and
/// struct with info about current title.
/// For current title compare ID with each movieID from topMovies.
/// Fill MovieName using priority of names.

}  // namespace TopFilmSelection

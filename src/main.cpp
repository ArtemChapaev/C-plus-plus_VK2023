#include <iostream>
#include <string>
#include <vector>

#include "printMovieNames.hpp"
#include "utils.hpp"

// this define may enable logging in loop
// #define DEBUG

int main(int argc, char *argv[]) {
    unsigned maxMinutes = 0;
    std::vector<std::string> filenames;

    int errorCode = HandleArguments(argc, argv, maxMinutes, filenames);
    if (errorCode) {
        return errorCode;
    }

    std::string ratingsFilename = FindNeededFilename(filenames, RATING_FILENAME);
    if (ratingsFilename.empty()) {
        std::cerr << "Wrong ratings filename\n";
        return 2;
    }

    std::string basicsFilename = FindNeededFilename(filenames, BASICS_FILENAME);
    if (basicsFilename.empty()) {
        std::cerr << "Wrong basics filename\n";
        return 3;
    }

    std::vector<std::string> topMovies;
    errorCode = GetTopMovies(ratingsFilename, basicsFilename, maxMinutes, topMovies);
    if (errorCode) {
        return errorCode;
    }

    std::string akasFilename = FindNeededFilename(filenames, AKAS_FILENAME);
    if (akasFilename.empty()) {
        std::cerr << "Wrong akas filename\n";
        return 4;
    }

    errorCode = PrintMovieNames(akasFilename, topMovies);
    if (errorCode) {
        return errorCode;
    }
    return 0;
}

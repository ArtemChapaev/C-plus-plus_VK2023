#include <iostream>
#include <string>
#include <vector>

#include "printMovieNames.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    unsigned maxMinutes = 0;
    std::vector<std::string> filenames;
    filenames.resize(3);

    int errorCode = HandleArguments(argc, argv, maxMinutes, filenames);
    if (errorCode) {
        return errorCode;
    }

    std::string ratingsFilename = filenames[0];
    std::string basicsFilename = filenames[1];

    std::vector<std::string> topMovies;
    errorCode = GetTopMovies(ratingsFilename, basicsFilename, maxMinutes, topMovies);
    if (errorCode) {
        return errorCode;
    }

    std::string akasFilename = filenames[2];

    errorCode = PrintMovieNames(akasFilename, topMovies);
    if (errorCode) {
        return errorCode;
    }
    return 0;
}

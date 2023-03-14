#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "pickRightMovies.hpp"
#include "pickTopTitles.hpp"

int HandleArguments(int argc, char *argv[], unsigned &maxMinutes, std::vector<std::string> &filenames) {
    if (argc != 5) {
        std::cerr << "Wrong amount of arguments\nNeed \"<minutes> <file1> <file2> <file3>\"\n";
        return -2;
    } else {
        try {
            maxMinutes = std::stoi(argv[1]);
        } catch (std::invalid_argument) {
            std::cerr << "Wrong max minutes value\n";
            return 1;
        }

        for (int i = 2; i < argc; ++i) {
            filenames.emplace_back(argv[i]);
        }
    }
    return 0;
}

std::string FindNeededFilename(const std::vector<std::string> &filenames, const std::string &neededFilename) {
    for (const auto &filename : filenames) {
        if (filename.find(neededFilename) != std::string::npos) {
            return filename;
        }
    }
    return "";
}

int GetTopMovies(std::string &ratingsFilename, std::string &basicsFilename, unsigned maxMinutes,
                 std::vector<std::string> &topMovies) {
#ifdef DEBUG
    std::cout << "topMovies.size() after every iteration of loop:\n"
#endif

        // initialize ("", INITIALIZE_RATING) for pick the best of all titles
        std::tuple<std::string, float>
            titleFromLastTop = std::make_tuple("", INITIALIZE_RATING);
    while (topMovies.size() < TOP_AMOUNT) {
        // here we store ordered top-500 (PICKED_TOP_AMOUNT) pair of "titleID-averageRating"
        std::vector<std::tuple<std::string, float>> topTitlesWithRating;

        int errorCode = PickTopTitles(ratingsFilename, topTitlesWithRating, titleFromLastTop);
        if (errorCode) {
            return errorCode;
        }

        errorCode = PickRightFilms(basicsFilename, topTitlesWithRating, maxMinutes, topMovies);
        if (errorCode) {
            return errorCode;
        }

        titleFromLastTop = topTitlesWithRating[PICKED_TOP_AMOUNT - 1];

#ifdef DEBUG
        std::cout << topMovies.size() << " " << std::flush;
#endif
    }
#ifdef DEBUG
    std::cout << std::endl;
#endif
    return 0;
}

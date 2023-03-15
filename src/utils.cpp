#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "pickRightMovies.hpp"
#include "pickTopTitles.hpp"

int HandleArguments(int argc, char *argv[], unsigned &maxMinutes, std::vector<std::string> &filenames) {
    if (argc != 5) {
        std::cerr << "Wrong amount of arguments\n $ ./program -minutes=<minutes>"
                  << "-ratings=<path> -basics=<path> -akas=<path>\n";
        return WRONG_ARG_COUNT;
    }

    for (int i = 1; i < 5; ++i) {
        std::string str = argv[i];
        std::string dataFromStr;
        switch (FindDataFromStr(str, dataFromStr)) {
            case MIN_OPTION_FLAG:
                try {
                    maxMinutes = std::stoi(dataFromStr);
                } catch (std::invalid_argument) {
                    std::cerr << "Wrong max minutes value\n";
                    return WRONG_MINUTES;
                }
                break;
            case RATING_OPTION_FLAG:
                filenames[0] = dataFromStr;
                break;
            case BASICS_OPTION_FLAG:
                filenames[1] = dataFromStr;
                break;
            case AKAS_OPTION_FLAG:
                filenames[2] = dataFromStr;
                break;
            default:
                break;
        }
    }

    if (!maxMinutes) {
        std::cerr << "No found max minute\n";
        return WRONG_MINUTES;
    } else if (filenames[0].empty()) {
        std::cerr << "No found rating file\n";
        return WRONG_RATING_FILENAME;
    } else if (filenames[1].empty()) {
        std::cerr << "No found basics file\n";
        return WRONG_BASICS_FILENAME;
    } else if (filenames[2].empty()) {
        std::cerr << "No found akas file\n";
        return WRONG_AKAS_FILENAME;
    }
    return 0;
}

int FindDataFromStr(std::string &inStr, std::string &outStr) {
    auto minFindPos = inStr.find(MIN_OPTION);
    auto ratFindPos = inStr.find(RATING_OPTION);
    auto basFindPos = inStr.find(BASICS_OPTION);
    auto akaFindPos = inStr.find(AKAS_OPTION);

    if (minFindPos != std::string::npos) {
        outStr = inStr.substr(MIN_OPTION.size());
        return MIN_OPTION_FLAG;
    }
    if (ratFindPos != std::string::npos) {
        outStr = inStr.substr(RATING_OPTION.size());
        return RATING_OPTION_FLAG;
    }
    if (basFindPos != std::string::npos) {
        outStr = inStr.substr(BASICS_OPTION.size());
        return BASICS_OPTION_FLAG;
    }
    if (akaFindPos != std::string::npos) {
        outStr = inStr.substr(AKAS_OPTION.size());
        return AKAS_OPTION_FLAG;
    }
    return DATA_NOT_FOUND;
}

int GetTopMovies(std::string &ratingsFilename, std::string &basicsFilename, unsigned maxMinutes,
                 std::vector<std::string> &topMovies) {
#ifdef DEBUG
    std::cout << "topMovies.size() after every iteration of loop:\n";
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

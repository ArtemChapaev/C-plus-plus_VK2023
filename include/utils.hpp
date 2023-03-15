#pragma once

#include <string>
#include <vector>

// this define may enable logging in loop
// #define DEBUG 1

const std::string MIN_OPTION = "-minutes=";
const std::string RATING_OPTION = "-ratings=";
const std::string BASICS_OPTION = "-basics=";
const std::string AKAS_OPTION = "-akas=";


enum optionFlags {
    DATA_NOT_FOUND, MIN_OPTION_FLAG, RATING_OPTION_FLAG, BASICS_OPTION_FLAG, AKAS_OPTION_FLAG
};

enum errors {
    WRONG_ARG_COUNT = -2,
    FILE_NOT_OPEN = -1,
    WRONG_MINUTES = 1,
    WRONG_RATING_FILENAME,
    WRONG_BASICS_FILENAME,
    WRONG_AKAS_FILENAME
};

const int INITIALIZE_RATING = 11;

int HandleArguments(int argc, char *argv[], unsigned &maxMinutes, std::vector<std::string> &filenames);
/// Parameters - input data and variables for write max minutes and filenames.
/// Return values - 0 or error.
/// Check passed arguments, search needed data.

int FindDataFromStr(std::string &inStr, std::string &outStr);
/// Parameters - str of data and empty str for result.
/// Return values - const int from optionFlags. int describe recieved data.
/// Find from inStr custom args.

int GetTopMovies(std::string &ratingsFilename, std::string &basicsFilename, unsigned maxMinutes,
                 std::vector<std::string> &topMovies);
/// Parameters - rating and basics filenames, maxMinutes from argv, empty vector for pick top movies.
/// Return values - 0 or error.
/// In loop find top titles and pick top movies while topMovies.size() != 10 (TOP_AMOUNT).

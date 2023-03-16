#pragma once

#include <string>
#include <vector>

// this define may enable logging in loop
// #define DEBUG 1

const int TOP_AMOUNT = 10;
const int MIN_VOTES = 1000;

const std::string MIN_OPTION = "--max-minute-count";
const std::string RATING_OPTION = "--title-ratings-path";
const std::string BASICS_OPTION = "--title-basics-path";
const std::string AKAS_OPTION = "--title-akas-path";

struct ConsoleArgs {
    unsigned maxMinutes;
    std::string ratingsFilename;
    std::string basicsFilename;
    std::string akasFilename;
};

ConsoleArgs HandleArguments(int argc, char *argv[]);
/// Parameters - input data.
/// Return value - struct of ConsoleArgs with needed data.
/// Check passed arguments, search needed data.

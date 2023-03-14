#pragma once

#include <string>
#include <vector>

const std::string RATING_FILENAME = "title.ratings.tsv";
const std::string BASICS_FILENAME = "title.basics.tsv";
const std::string AKAS_FILENAME = "title.akas.tsv";

const std::string LOGFILE_NAME = "logfile.log";

const int INITIALIZE_RATING = 11;

int HandleArguments(int argc, char *argv[], unsigned &maxMinutes, std::vector<std::string> &filenames);
/// Parameters - input data and variables for write max minutes and filenames.
/// Return values - 0 or error.
/// Check passed arguments, search needed data.

std::string FindNeededFilename(const std::vector<std::string> &filenames, const std::string &neededFilename);
/// Parameters - vector of all filenames, string of needed filename.
/// Return values - needed filename or empty str.
/// Search needed filename in array of filenames.

int GetTopMovies(std::string &ratingsFilename, std::string &basicsFilename, unsigned maxMinutes,
                 std::vector<std::string> &topMovies);
/// Parameters - rating and basics filenames, maxMinutes from argv, empty vector for pick top movies.
/// Return values - 0 or error.
/// In loop find top titles and pick top movies while topMovies.size() != 10 (TOP_AMOUNT).

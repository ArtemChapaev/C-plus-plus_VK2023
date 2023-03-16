#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace TopFilmSelection {

const int TOP_AMOUNT = 10;
const int MIN_VOTES = 1000;

struct TopMovie {
    std::string ID;
    float rating;
};

std::vector<std::string> PickTopMovies(const std::string &ratingsFilename, const std::string &basicsFilename,
                                       unsigned maxMinutes);
/// Parameters - ratings and basics filenames, maxMinutes from argv.
/// Return value - full vector with picked top movies.
/// Read basics file and select movies. Search movie's rating in ratings file.
/// Pick movies with the best ratings and return their IDs.

std::string ReadMovieBasics(std::ifstream &file, unsigned maxMinutes);
/// Parameters - ifstream for reading, maxMinutes from argv.
/// Return value - titleID if task's conditions are complete else empty string.
/// Read title from file and if it is movie and relevant return ID.

float SearchMovieRating(std::ifstream &file, std::string &movieID);
/// Parameters - ifstream for reading, movieID that need search of rating.
/// Return value - rating if it is found and is relevant else 0.
/// Read file while don't find need movieID or ID that is bigger then movieID.
/// Check numVotes and return needed rating.

void InsertRatingToTop(std::vector<TopMovie> &topMoviesWithRating, std::string &movieID, float movieRating);
/// Parameters - vector of top pair "movieID-movieRating", info about current movie.
/// Insert current movie into topMoviesWithRating. Keep topMoviesWithRating always in order.

}  // namespace TopFilmSelection

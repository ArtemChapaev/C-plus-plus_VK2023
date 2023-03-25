#include "pickTopMovies.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace TopFilmSelection {

std::vector<std::string> PickTopMovies(const std::string &ratingsFilename, const std::string &basicsFilename,
                                       unsigned maxMinutes) {
    std::ifstream ratingsFile(ratingsFilename);
    if (!ratingsFile.is_open()) {
        throw std::logic_error("error in open rating file\n");
    }
    std::ifstream basicsFile(basicsFilename);
    if (!basicsFile.is_open()) {
        throw std::logic_error("error in open basics file\n");
    }

    std::string first_line;
    getline(ratingsFile, first_line);
    getline(basicsFile, first_line);

    // vector of top-10 (TOP_AMOUNT) pair of "movieID-movieRating"
    std::vector<TopMovie> topMoviesWithRating;
    while (!ratingsFile.eof() && !basicsFile.eof()) {
        std::string movieID = ReadMovieBasics(basicsFile, maxMinutes);
        // we check only relevant movie from basics file
        if (movieID.empty()) {
            continue;
        }

        // find rating of current movie
        float movieRating = SearchMovieRating(ratingsFile, movieID);
        // we check only relevant rating. here we also check machine inaccuracy of float
        if (movieRating < EPSILON) {
            continue;
        }

        if (topMoviesWithRating.size() == TOP_AMOUNT) {
            // if rating so little we skip this movie
            if (topMoviesWithRating[TOP_AMOUNT - 1].rating >= movieRating) {
                continue;
            }
            topMoviesWithRating.pop_back();
        }
        // insert current data into topMoviesWithRating
        InsertRatingToTop(topMoviesWithRating, movieID, movieRating);
    }
    // pick only ID from pair "movieID-movieRating"
    std::vector<std::string> topMovies;
    for (const auto &topMovie : topMoviesWithRating) {
        topMovies.push_back(topMovie.ID);
    }

    ratingsFile.close();
    basicsFile.close();
    return topMovies;
}

std::string ReadMovieBasics(std::ifstream &file, const unsigned maxMinutes) {
    std::string titleID, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes,
        genres;

    getline(file, titleID, '\t');
    getline(file, titleType, '\t');
    getline(file, primaryTitle, '\t');
    getline(file, originalTitle, '\t');
    getline(file, isAdult, '\t');
    getline(file, startYear, '\t');
    getline(file, endYear, '\t');
    getline(file, runtimeMinutes, '\t');
    getline(file, genres);

    // empty line handler
    if (titleID.empty()) {
        return "";
    }

    // if last column is empty, data is bad
    if (genres.empty()) {
        throw std::logic_error("error in akas file: wrong data\n");
    }

    if (titleID == "\\N" || titleType == "\\N" || isAdult == "\\N" || runtimeMinutes == "\\N") {
        return "";
    }

    if (std::stoi(runtimeMinutes) > maxMinutes || std::stoi(isAdult) || titleType != "movie") {
        return "";
    }

    return titleID;
}

float SearchMovieRating(std::ifstream &file, const std::string &movieID) {
    std::string titleID, averageRating, numVotes;
    while (movieID != titleID) {
        getline(file, titleID, '\t');
        getline(file, averageRating, '\t');
        getline(file, numVotes);

        // checking case of titleID = movieID + x. where x = "0" or other digit string
        if (titleID.size() > movieID.size() && titleID.substr(movieID.size()) == movieID) {
            continue;
        }

        // checking case "movieID don't have rating" and case of file.eof()
        if (titleID > movieID || file.eof()) {
            return 0;
        }
    }

    // if last column is empty, data is bad
    if (numVotes.empty()) {
        throw std::logic_error("error in ratings file: wrong data\n");
    }

    if (averageRating == "\\N" || numVotes == "\\N") {
        return 0;
    }

    if (std::stoi(numVotes) < MIN_VOTES) {
        return 0;
    }

    return std::stof(averageRating);
}

void InsertRatingToTop(std::vector<TopMovie> &topMoviesWithRating, const std::string &movieID,
                       const float movieRating) {
    // binary search of right place for insertion
    auto insertIter =
        std::lower_bound(topMoviesWithRating.begin(), topMoviesWithRating.end(), movieRating,
                         [](const TopMovie &movie, float rating) { return movie.rating >= rating; });

    int insertionIndex = insertIter - topMoviesWithRating.begin();

    // firstly point to current title, after swap help not lose some title
    TopMovie movieForInsert = {movieID, movieRating};

    // sequentially move all elements of vector. we begin from insert current title
    for (int i = insertionIndex; i < topMoviesWithRating.size(); ++i) {
        std::swap(topMoviesWithRating[i], movieForInsert);
    }

    topMoviesWithRating.push_back(movieForInsert);
}

}  // namespace TopFilmSelection

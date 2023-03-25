#include "printMovieNames.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace TopFilmSelection {

void PrintMovieNames(const std::string &filename, const std::vector<std::string> &topMovies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("error in open akas file\n");
    }

    std::string first_line;
    getline(file, first_line);

    std::vector<MovieName> movieNames;
    movieNames.resize(topMovies.size());

    std::string titleID, ordering, title, region, language, types, attributes, isOriginalTitle;

    while (!file.eof()) {
        getline(file, titleID, '\t');
        getline(file, ordering, '\t');
        getline(file, title, '\t');
        getline(file, region, '\t');
        getline(file, language, '\t');
        getline(file, types, '\t');
        getline(file, attributes, '\t');
        getline(file, isOriginalTitle);

        // if last column is empty, data is bad
        if (isOriginalTitle.empty()) {
            throw std::logic_error("error in reading akas file\n");
        }

        AkasInfo info{titleID, title, region, language, isOriginalTitle};
        FindMovieName(topMovies, movieNames, info);
    }

    for (int i = 0; i < movieNames.size(); ++i) {
        std::cout << i + 1 << ") " << movieNames[i].name << std::endl;
    }

    file.close();
}

void FindMovieName(const std::vector<std::string> &topMovies, std::vector<MovieName> &movieNames,
                   const AkasInfo titleInfo) {
    for (int i = 0; i < topMovies.size(); ++i) {
        // find needed name for condition of task
        if (topMovies[i] != titleInfo.titleID) {
            continue;
        }
        // if there is already ru-name, we don't use original or other names
        if (movieNames[i].wasRuName) {
            continue;
        }

        // firstly we check ru-name, then original name and other names
        if (titleInfo.region == "RU" || titleInfo.language == "ru") {
            movieNames[i].name = titleInfo.title;
            movieNames[i].wasRuName = true;

            // if this title is original we use second priority
        } else if (std::stoi(titleInfo.isOriginalTitle)) {
            movieNames[i].name = titleInfo.title;
            movieNames[i].wasOriginalName = true;

            // if there is already original name, we don't use other names
        } else if (!movieNames[i].wasOriginalName) {
            movieNames[i].name = titleInfo.title;
        }

        // we found ID for this title from topMovies, so we can use 'break'
        break;
    }
}

}  // namespace TopFilmSelection

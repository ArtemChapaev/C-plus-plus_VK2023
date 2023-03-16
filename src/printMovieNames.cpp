#include "printMovieNames.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace TopFilmSelection {

void PrintMovieNames(std::string &filename, std::vector<std::string> &topMovies) {
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

        for (int i = 0; i < topMovies.size(); ++i) {
            // find needed name for condition of task
            if (topMovies[i] == titleID && !movieNames[i].wasRuName) {
                if (region == "RU" || language == "ru") {
                    movieNames[i].name = title;
                    movieNames[i].wasRuName = true;
                } else if (std::stoi(isOriginalTitle)) {
                    movieNames[i].name = title;
                    movieNames[i].wasOriginalName = true;
                } else if (!movieNames[i].wasOriginalName) {
                    movieNames[i].name = title;
                }
            }
        }
    }

    for (int i = 0; i < movieNames.size(); ++i) {
        std::cout << i + 1 << ") " << movieNames[i].name << std::endl;
    }
}

}  // namespace TopFilmSelection

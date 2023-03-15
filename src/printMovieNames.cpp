#include "printMovieNames.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int PrintMovieNames(std::string &filename, std::vector<std::string> &rightTitles) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "error in open akas filename" << std::endl;
        return FILE_NOT_OPEN;
    }

    std::string first_line;
    getline(file, first_line);

    // first flag show priority of ru-name, second - priority of original name
    std::vector<std::tuple<std::string, bool, bool>> movieNames;
    movieNames.resize(TOP_AMOUNT);

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

        for (int i = 0; i < TOP_AMOUNT; ++i) {
            if (rightTitles[i] == titleID && !std::get<1>(movieNames[i])) {
                if (region == "RU" || language == "ru") {
                    std::get<0>(movieNames[i]) = title;
                    std::get<1>(movieNames[i]) = true;
                } else if (std::stoi(isOriginalTitle)) {
                    std::get<0>(movieNames[i]) = title;
                    std::get<2>(movieNames[i]) = true;
                } else if (!std::get<2>(movieNames[i])) {
                    std::get<0>(movieNames[i]) = title;
                }
            }
        }
    }

    for (int i = 0; i < TOP_AMOUNT; ++i) {
        std::cout << i + 1 << ") " << std::get<0>(movieNames[i]) << std::endl;
    }

    return 0;
}

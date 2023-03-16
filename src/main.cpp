#include <iostream>
#include <string>
#include <vector>

#include "pickTopMovies.hpp"
#include "printMovieNames.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    auto [maxMinutes, ratingsFilename, basicsFilename, akasFilename] = HandleArguments(argc, argv);

    std::vector<std::string> topMovies = PickTopMovies(ratingsFilename, basicsFilename, maxMinutes);

    PrintMovieNames(akasFilename, topMovies);
    return 0;
}

ConsoleArgs HandleArguments(int argc, char *argv[]) {
    if (argc != 9) {
        throw std::logic_error(
            "Wrong amount of arguments\n $ ./program --max-minute-count 160 title-ratings-path "
            "data/title.ratings.tsv --title-basics-path data/title.basics.tsv --title-akas-path "
            "data/title.akas.tsv\n");
    }

    ConsoleArgs arguments;
    for (int i = 0; i < 4; ++i) {
        int key = i * 2 + 1;
        int value = i * 2 + 2;

        if (argv[key] == MIN_OPTION) {
            // checking of value for maxMinutes
            try {
                arguments.maxMinutes = std::stoi(argv[value]);
            } catch (std::invalid_argument) {
                throw std::logic_error("Wrong max minutes value\n");
            }
        } else if (argv[key] == RATING_OPTION) {
            arguments.ratingsFilename = argv[value];
        } else if (argv[key] == BASICS_OPTION) {
            arguments.basicsFilename = argv[value];
        } else if (argv[key] == AKAS_OPTION) {
            arguments.akasFilename = argv[value];
        }
    }

    // checking existence of parameters
    if (!arguments.maxMinutes) {
        throw std::logic_error("No found max minute value\n");
    } else if (arguments.ratingsFilename.empty()) {
        throw std::logic_error("No found ratings filename\n");
    } else if (arguments.basicsFilename.empty()) {
        throw std::logic_error("No found basics filename\n");
    } else if (arguments.akasFilename.empty()) {
        throw std::logic_error("No found akas filename\n");
    }
    return arguments;
}

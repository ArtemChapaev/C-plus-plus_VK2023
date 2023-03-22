#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "pickTopMovies.hpp"
#include "printMovieNames.hpp"

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

int main(int argc, char *argv[]) {
    try {
        auto [maxMinutes, ratingsFilename, basicsFilename, akasFilename] = HandleArguments(argc, argv);

        std::vector<std::string> topMovies =
            TopFilmSelection::PickTopMovies(ratingsFilename, basicsFilename, maxMinutes);

        TopFilmSelection::PrintMovieNames(akasFilename, topMovies);
    }

    catch (std::exception &e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}

ConsoleArgs HandleArguments(int argc, char *argv[]) {
    if (argc != 9) {
        throw std::logic_error(
            "Wrong amount of arguments\n $ ./program --max-minute-count 160 --title-ratings-path "
            "data/title.ratings.tsv --title-basics-path data/title.basics.tsv --title-akas-path "
            "data/title.akas.tsv\n");
    }

    ConsoleArgs arguments;
    for (int i = 0; i < 4; ++i) {
        int key = i * 2 + 1;
        int value = i * 2 + 2;

        if (argv[key] == MIN_OPTION) {
            // checking of value for maxMinutes
            int numArgument = std::stoi(argv[value]);
            if (numArgument <= 0) {
                throw std::logic_error("Max minutes cannot be equal to or less then zero\n");
            }
            arguments.maxMinutes = numArgument;
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
    }
    if (arguments.ratingsFilename.empty()) {
        throw std::logic_error("No found ratings filename\n");
    }
    if (arguments.basicsFilename.empty()) {
        throw std::logic_error("No found basics filename\n");
    }
    if (arguments.akasFilename.empty()) {
        throw std::logic_error("No found akas filename\n");
    }
    return arguments;
}

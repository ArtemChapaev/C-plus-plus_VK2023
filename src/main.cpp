#include <iostream>
#include <string>
#include <vector>

#include "hadleArguments.hpp"
#include "pickTopMovies.hpp"
#include "printMovieNames.hpp"

int main(int argc, char* argv[]) {
    try {
        auto [maxMinutes, ratingsFilename, basicsFilename, akasFilename] =
            ArgumentParsing::HandleArguments(argc, argv);

        std::vector<std::string> topMovies =
            TopFilmSelection::PickTopMovies(ratingsFilename, basicsFilename, maxMinutes);

        TopFilmSelection::PrintMovieNames(akasFilename, topMovies);
    }

    catch (std::exception& e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}

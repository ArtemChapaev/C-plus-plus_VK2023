#include <iostream>

#include "parseOperations.hpp"

int main(int argc, char *argv[]) {
    try {
        auto firstOperation = OperatorParsing::HandleArguments(argc, argv);

        firstOperation->HandleEndOfInput();
    }

    catch (std::exception &e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}
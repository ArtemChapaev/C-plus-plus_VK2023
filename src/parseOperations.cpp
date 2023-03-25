#include "parseOperations.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "operations.hpp"

namespace OperatorParsing {

std::shared_ptr<Operations::IOperation> HandleArguments(const int argc, char *argv[]) {
    if (argc != 2) {
        throw std::logic_error(
            "Wrong amount of arguments\n$ ./text_processor '<operator> <argument>[ | <operator> <argument> ...]'\n");
    }
    std::stringstream input;
    input << argv[1];

    std::shared_ptr<Operations::IOperation> firstOperation;
    bool isFirstLexeme = true;

    // flag shows what lexeme we need. this can be operation or arguments
    bool isNeededOperation = true;
    bool requiredNextArgument = false;

    std::shared_ptr<Operations::IOperation> lastOperation;
    while (!input.eof()) {
        std::string str;
        input >> str;

        // we check operation if it's needed
        if (isNeededOperation) {
            std::shared_ptr<Operations::IOperation> currOperation =
                ParseOperation(str, lastOperation, requiredNextArgument);
            isNeededOperation = false;

            if (isFirstLexeme) {
                firstOperation = currOperation;
                isFirstLexeme = false;
            }
            continue;
        }

        if (str == PIPE) {
            isNeededOperation = true;
        } else {
            if (!requiredNextArgument) {
                throw std::logic_error("Wrong request\nBad argument position\n");
            }
            lastOperation->ProcessLine(str);
            requiredNextArgument = false;
        }
    }
    return firstOperation;
}

std::shared_ptr<Operations::IOperation> ParseOperation(const std::string &str,
                                           std::shared_ptr<Operations::IOperation> &lastOperation,
                                           bool &requiredNextArgument) {
    std::shared_ptr<Operations::IOperation> currOperation;

    if (str == CAT_OPERATION) {
        currOperation = std::make_shared<Operations::CatOperation>();
        requiredNextArgument = true;
    } else if (str == ECHO_OPERATION) {
        currOperation = std::make_shared<Operations::EchoOperation>();
        requiredNextArgument = true;
    } else if (str == UNIQ_OPERATION) {
        currOperation = std::make_shared<Operations::UniqOperation>();
        requiredNextArgument = false;
    } else {
        throw std::logic_error("Wrong request\nThere isn't operator in needed position\n");
    }

    // connecting current operation with last one
    if (lastOperation) {
        lastOperation->SetNextOperation(currOperation);
    }

    lastOperation = currOperation;
    return currOperation;
}

}  // namespace OperatorParsing

#include "catOperation.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Operations {

void CatOperation::AddInputData(const std::string &str) {
    inputData.push_back(str);
}

void CatOperation::ProcessLine(const std::string &str) {
    // firstly check file
    std::ifstream file(str);
    if (!file.is_open()) {
        throw std::logic_error("Wrong file\n");
    }

    // handling of text from file
    while (!file.eof()) {
        std::string str;
        getline(file, str);
        fileData.push_back(str);
    }
}

void CatOperation::SetNextOperation(const std::shared_ptr<IOperation> &operation) {
    nextOperation = operation;
}

void CatOperation::HandleEndOfInput() {
    if (nextOperation) {
        // output inputData
        for (const auto &inputStr : inputData) {
            nextOperation->AddInputData(inputStr);
        }

        // output fileData
        for (const auto &fileStr : fileData) {
            nextOperation->AddInputData(fileStr);
        }
        nextOperation->HandleEndOfInput();
    } else {
        // output inputData
        for (const auto &inputStr : inputData) {
            std::cout << inputStr << std::endl;
        }

        // output fileData
        for (const auto &fileStr : fileData) {
            std::cout << fileStr << std::endl;
        }
    }
}

}  // namespace Operations

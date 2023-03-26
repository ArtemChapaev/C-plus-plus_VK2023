#include "operations.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Operations {

void CatOperation::AddInputData(const std::string &str) { inputData.push_back(str); }

void CatOperation::ProcessLine(const std::string &str) { filename = str; }

void CatOperation::SetNextOperation(const std::shared_ptr<IOperation> &operation) {
    nextOperation = operation;
}

void CatOperation::HandleEndOfInput() {
    // firstly check file. if it's wrong we don't handle inputData
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("Wrong file\n");
    }

    // basic exception safety
    try {
        // handling of inputData
        for (const auto &inputStr : inputData) {
            if (nextOperation) {
                nextOperation->AddInputData(inputStr);
            } else {
                std::cout << inputStr << std::endl;
            }
        }

        // handling of text from file
        while (!file.eof()) {
            std::string str;
            getline(file, str);
            if (nextOperation) {
                nextOperation->AddInputData(str);
            } else {
                std::cout << str << std::endl;
            }
        }

        if (nextOperation) {
            nextOperation->HandleEndOfInput();
        }
    } catch (...) {
        file.close();
        throw;
    }

    file.close();
}

void EchoOperation::AddInputData(const std::string &str) { inputData.push_back(str); }

void EchoOperation::ProcessLine(const std::string &str) { text = str; }

void EchoOperation::SetNextOperation(const std::shared_ptr<IOperation> &operation) {
    nextOperation = operation;
}

void EchoOperation::HandleEndOfInput() {
    if (nextOperation) {
        nextOperation->AddInputData(text);
        nextOperation->HandleEndOfInput();
    } else {
        std::cout << text << std::endl;
    }
}

void UniqOperation::AddInputData(const std::string &str) { inputData.push_back(str); }

void UniqOperation::ProcessLine(const std::string &str) { lineForProcessing = str; }

void UniqOperation::SetNextOperation(const std::shared_ptr<IOperation> &operation) {
    nextOperation = operation;
}

void UniqOperation::HandleEndOfInput() {
    std::string lastStr = "";

    for (const auto &str : inputData) {
        if (str != lastStr) {
            if (nextOperation) {
                nextOperation->AddInputData(str);
            } else {
                std::cout << str << std::endl;
            }
        }

        lastStr = str;
    }

    if (nextOperation) {
        nextOperation->HandleEndOfInput();
    }
}

}  // namespace Operations

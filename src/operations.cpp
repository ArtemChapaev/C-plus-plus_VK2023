#include "operations.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Operations {

void CatOperation::AddInputData(const std::string &str) { inputData.push_back(str); }

void CatOperation::ProcessLine(const std::string &str) {
    // firstly check file
    std::ifstream file(str);
    if (!file.is_open()) {
        throw std::logic_error("Wrong file\n");
    }

    // basic exception safety
    try {
        // handling of text from file
        while (!file.eof()) {
            std::string str;
            getline(file, str);
            fileData.push_back(str);
        }
    } catch (...) {
        file.close();
        throw;
    }

    file.close();
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

// echo don't use InputData
void EchoOperation::AddInputData(const std::string &str) {}

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

// UniqOperation don't work with arguments
void UniqOperation::ProcessLine(const std::string &str) {}

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

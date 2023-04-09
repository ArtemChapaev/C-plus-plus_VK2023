#include "uniqOperation.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace Operations {

void UniqOperation::AddInputData(const std::string &str) {
    inputData.push_back(str);
}

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

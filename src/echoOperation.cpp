#include "echoOperation.hpp"

#include <iostream>
#include <memory>
#include <string>

namespace Operations {

// echo don't use InputData
void EchoOperation::AddInputData(const std::string &str) {}

void EchoOperation::ProcessLine(const std::string &str) {
    text = str;
}

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

}  // namespace Operations

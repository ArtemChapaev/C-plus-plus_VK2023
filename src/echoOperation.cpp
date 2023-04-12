#include "echoOperation.hpp"

#include <iostream>

namespace Operations {

void EchoOperation::AddInputData(const std::string &str) {}

void EchoOperation::ProcessLine(const std::string &str) {
    text = str;
}

void EchoOperation::SetNextOperation(std::shared_ptr<IOperation> operation) {
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

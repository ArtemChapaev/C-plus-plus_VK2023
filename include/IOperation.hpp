#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Operations {

class IOperation {
   public:
    virtual ~IOperation() {}

    virtual void AddInputData(const std::string &str) = 0;
    virtual void ProcessLine(const std::string &str) = 0;
    virtual void SetNextOperation(const std::shared_ptr<IOperation> &operation) = 0;
    virtual void HandleEndOfInput() = 0;
};

}  // namespace Operations

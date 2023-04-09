#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IOperation.hpp"

namespace Operations {

class UniqOperation final : public IOperation {
   public:
    void AddInputData(const std::string &str) override;
    void ProcessLine(const std::string &str) override;  // UniqOperation don't work with arguments
    void SetNextOperation(const std::shared_ptr<IOperation> &operation) override;
    void HandleEndOfInput() override;

   private:
    std::vector<std::string> inputData;
    std::shared_ptr<IOperation> nextOperation;
};

}  // namespace Operations

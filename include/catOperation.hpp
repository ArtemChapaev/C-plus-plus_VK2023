#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IOperation.hpp"

namespace Operations {
class CatOperation final : public IOperation {
   public:
    void AddInputData(const std::string &str) override;
    void ProcessLine(const std::string &str) override;
    void SetNextOperation(std::shared_ptr<IOperation> operation) override;
    void HandleEndOfInput() override;

   private:
    std::vector<std::string> inputData;
    std::vector<std::string> fileData;
    std::shared_ptr<IOperation> nextOperation;
};
}  // namespace Operations

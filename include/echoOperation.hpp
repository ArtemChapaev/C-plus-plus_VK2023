#pragma once

#include <memory>
#include <string>

#include "IOperation.hpp"

namespace Operations {

class EchoOperation final : public IOperation {
   public:
    void AddInputData(const std::string &str) override;  // echo don't use InputData
    void ProcessLine(const std::string &str) override;
    void SetNextOperation(const std::shared_ptr<IOperation> &operation) override;
    void HandleEndOfInput() override;

   private:
    std::string text;
    std::shared_ptr<IOperation> nextOperation;
};

}  // namespace Operations

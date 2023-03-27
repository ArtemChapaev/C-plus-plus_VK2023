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

class CatOperation : public IOperation {
   public:
    void AddInputData(const std::string &str) override;
    void ProcessLine(const std::string &str) override;
    void SetNextOperation(const std::shared_ptr<IOperation> &operation) override;
    void HandleEndOfInput() override;

   private:
    std::vector<std::string> inputData;
    std::string filename;
    std::shared_ptr<IOperation> nextOperation;
};

class EchoOperation : public IOperation {
   public:
    void AddInputData(const std::string &str) override;
    void ProcessLine(const std::string &str) override;
    void SetNextOperation(const std::shared_ptr<IOperation> &operation) override;
    void HandleEndOfInput() override;

   private:
    std::vector<std::string> inputData;  // echo don't use it
    std::string text;
    std::shared_ptr<IOperation> nextOperation;
};

class UniqOperation : public IOperation {
   public:
    void AddInputData(const std::string &str) override;
    void ProcessLine(const std::string &str) override;
    void SetNextOperation(const std::shared_ptr<IOperation> &operation) override;
    void HandleEndOfInput() override;

   private:
    std::vector<std::string> inputData;
    std::string lineForProcessing;  // uniq don't use it
    std::shared_ptr<IOperation> nextOperation;
};

}  // namespace Operations

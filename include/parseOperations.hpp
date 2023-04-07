#pragma once

#include <memory>
#include <string>

#include "IOperation.hpp"

namespace OperatorParsing {

const std::string CAT_OPERATION = "cat";
const std::string ECHO_OPERATION = "echo";
const std::string UNIQ_OPERATION = "uniq";
const std::string PIPE = "|";

std::shared_ptr<Operations::IOperation> HandleArguments(const int argc, char *argv[]);
/// Parameters - input data.
/// Return value - shared_ptr for first operation in parsing.
/// Check passed argument, parse it. Search operations, arguments and pipes. Create chain of operations

std::shared_ptr<Operations::IOperation> ParseOperation(const std::string &str,
                                                       std::shared_ptr<Operations::IOperation> &lastOperation,
                                                       bool &requiredNextArgument);
/// Parameters - input lexeme for identifying, last operation in chain, bool value for checking next lexeme.
/// Return value - shared_ptr for current operation.
/// Check passed str, identify operation and connect with chain.

}  // namespace OperatorParsing
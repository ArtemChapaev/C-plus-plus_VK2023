#pragma once

#include "IOperation.hpp"

namespace OperatorParsing {

std::shared_ptr<Operations::IOperation> HandleArguments(const int argc, char *argv[]);
/// Parameters - input data.
/// Return value - shared_ptr for first operation in parsing.
/// Check passed argument, parse it. Search operations, arguments and pipes. Create chain of operations

}  // namespace OperatorParsing

cmake_minimum_required(VERSION 3.16)
project(text_processor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(text_processor /
        src/catOperation.cpp /
        src/echoOperation.cpp /
        src/uniqOperation.cpp /
        src/parseOperations.cpp /
        src/main.cpp /
        )

add_compile_options(-Wall -Wextra -pedantic -Werror)
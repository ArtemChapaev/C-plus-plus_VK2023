cmake_minimum_required(VERSION 3.16)
project(hw1)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(hw1 /
        src/main.cpp /
        src/utils.cpp /
        src/pickTopTitles.cpp /
        src/pickRightMovies.cpp /
        src/printMovieNames.cpp /
        )

add_compile_options(-Wall -Wextra -pedantic -Werror)

cmake_minimum_required(VERSION 3.16)
project(imdb_top_searcher)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(imdb_top_searcher /
        src/main.cpp /
        src/hadleArguments.cpp /
        src/pickTopMovies.cpp /
        src/printMovieNames.cpp /
        )

add_compile_options(-Wall -Wextra -pedantic -Werror)

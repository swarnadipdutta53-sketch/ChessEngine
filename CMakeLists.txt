cmake_minimum_required(VERSION 3.20)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ChessEngine

    mainAi.cpp
    Helper.cpp
    BoardIO.cpp
    Board.cpp
    legalMovesGenerator.cpp
    moveValidations.cpp
    Evaluator.cpp
    Minimax.cpp
    ChessAI.cpp
    Zobrist.cpp
)

if(MSVC)

    target_compile_options(
        ChessEngine
        PRIVATE
        /W4
    )

else()

    target_compile_options(
        ChessEngine
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# if(CMAKE_BUILD_TYPE STREQUAL "Debug")

#     target_compile_options(
#         ChessEngine
#         PRIVATE
#         -fsanitize=address,undefined
#     )

#     target_link_options(
#         ChessEngine
#         PRIVATE
#         -fsanitize=address,undefined
#     )

# endif()
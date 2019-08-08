cmake_minimum_required(VERSION 3.14)
project(minimax)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(CURSES_PATHS curses_implementation/curses_game.cpp curses_implementation/curses_game.hpp curses_implementation/curses_wrapper.cpp curses_implementation/curses_wrapper.hpp)

set(STDIO_PATHS stdio_implementation/tic_tac_toe.cpp stdio_implementation/tic_tac_toe.hpp)

set(COMMON_TOOLS_PATH common_tools/common_tools.cpp common_tools/common_tools.hpp minimax_algorithm/minimax_algorithm.cpp minimax_algorithm/minimax_algorithm.hpp)

add_executable(minimax main.cpp ${STDIO_PATHS} ${CURSES_PATHS} ${COMMON_TOOLS_PATH})
target_link_libraries(minimax -lncurses)
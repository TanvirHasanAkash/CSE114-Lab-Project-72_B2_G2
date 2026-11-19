cmake_minimum_required(VERSION 3.20)


project(TicTacToe VERSION 1.0.0 LANGUAGES C)


set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


add_executable(TicTacToe 
	src/main.c
)


if(MSVC)
	add_compile_options(TicTacToe PRIVATE /W4 /WX)
else()
	add_compile_options(TicTacToe PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow)
endif()

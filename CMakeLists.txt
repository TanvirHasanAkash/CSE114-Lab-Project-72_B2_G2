cmake_minimum_required(VERSION 3.20)


project(TicTacToe VERSION 1.0.0 LANGUAGES C)


set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/$<LOWER_CASE:$<CONFIG>>")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb")

set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb")


add_executable(TicTacToe
	src/main.c
)


if(MSVC)
	target_compile_options(TicTacToe PRIVATE /W4 /WX)
else()
	target_compile_options(TicTacToe PRIVATE -Wall -Wextra -Wpedantic -Werror -Wshadow)
endif()

if(MSVC)
	target_compile_options(TicTacToe PRIVATE
		$<$<CONFIG:Release>:/O2 /Oi /Ot /GL /arch:AVX2 /fp:fast>
	)
	target_link_options(TicTacToe PRIVATE
		$<$<CONFIG:Release>:/LTCG /OPT:REF /OPT:ICF>
	)
else()
	target_compile_options(TicTacToe PRIVATE
		$<$<CONFIG:Release>:-O3 -march=native -mtune=native -ffunction-sections -fdata-sections>
	)
	target_link_options(TicTacToe PRIVATE
		$<$<CONFIG:Release>:-Wl,--gc-sections -s>
	)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
	set_property(TARGET TicTacToe PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else()
	message(WARNING "IPO/LTO not supported: ${ipo_error}")
endif()

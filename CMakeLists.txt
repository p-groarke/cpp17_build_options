cmake_minimum_required(VERSION 3.8.0)
project(build_options CXX)

# Simple options.
set(MY_STRING "a string")
set(MY_INT 42)
option(MY_BOOL "A boolean." On)

# Rudimentary c++ version check. CMake supports much finer grained feature inquiry.
set(CPP_VERSION 98)
if ("cxx_std_11" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
	set(CPP_VERSION 11)
endif()
if ("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
	set(CPP_VERSION 14)
endif()
if ("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
	set(CPP_VERSION 17)
endif()

message("Your compiler supports : cpp${CPP_VERSION}")
set(CMAKE_CXX_STANDARD ${CPP_VERSION})

configure_file("src/build_options.h.in"
	"include/build_options.h")

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "src/*.hpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_BINARY_DIR}/include")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra #-Wpedantic
		-Werror)# -fno-exceptions)# -fno-rtti)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra #-Wpedantic
		-Werror)# -fno-exceptions)# -fno-rtti)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)

endif()

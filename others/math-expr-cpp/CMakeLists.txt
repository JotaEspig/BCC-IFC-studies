cmake_minimum_required(VERSION 2.8.5...3.28.2)
project(mathexpr)

# CMake settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(Doxygen OPTIONAL_COMPONENTS dot)

# =-=-=-=-=-=-= DOCS =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    message("Doxygen found. You can use `make docs`")

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen not found. You won't be able to use `make docs`")
endif (DOXYGEN_FOUND)


# =-=-=-=-=-=-= LIBRARY =-=-=-=-=-=-=
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
	${SOURCE_DIR}/expr.cpp
	${SOURCE_DIR}/greetings.cpp
	${SOURCE_DIR}/symbol.cpp
)

# Adding mathexpr shared library
add_library(mathexpr SHARED ${SOURCE_FILES})

# Libraries
target_link_libraries(
    mathexpr
    PRIVATE
    stdc++
)

# Header files
target_include_directories(
    mathexpr
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)


# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bin)

# Source files
set(
    TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
)

# Adding executables for testing
add_executable(tests ${TEST_SOURCE_FILES})

# Libraries
target_link_directories(
    tests
    PRIVATE
    ./lib
)
target_link_libraries(
    tests
    PRIVATE
    mathexpr
    stdc++
)

# Header files
target_include_directories(
    tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

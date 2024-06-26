cmake_minimum_required(VERSION 2.8.5...3.27.5)
project(matrix-calculator)

# Debug mode
set(FLAGS "-Wall -Wextra")
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# CMake settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS} -g3 -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS} -O3")

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


# =-=-=-=-=-=-= EXECUTABLE =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
)

# Adding executables
add_executable(matrix-calculator ${SOURCE_FILES})

# Libraries
target_link_directories(
    matrix-calculator
    PRIVATE
)
target_link_libraries(
    matrix-calculator
    PRIVATE
    stdc++
)

# Header files
target_include_directories(
    matrix-calculator
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
)

cmake_minimum_required(VERSION 3.15)
project(ripshomo)

# GUDHI requires C++14 or newer
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary dependencies
find_package(Boost REQUIRED)
# Optional: find_package(CGAL REQUIRED)

add_executable(main
    src/main.cpp include/Resources/filereaders.cpp
)

add_executable(generate_circle
    src/Circlegenerator.cpp
)

# Set the include directories to point to the GUDHI headers
include_directories(main PRIVATE
    ${Boost_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include/Resources
    ${PROJECT_SOURCE_DIR}/include/include
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-gdwarf-4)
endif()





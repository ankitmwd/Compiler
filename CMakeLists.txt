# filepath: /home/ankit/compiler/MyProject/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(compiler)

set(CMAKE_CXX_STANDARD 20)
# Add an executable
add_executable(hydro src/main.cpp)
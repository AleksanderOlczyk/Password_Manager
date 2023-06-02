cmake_minimum_required(VERSION 3.25)
project(projekt01)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(main main.cpp loginMenu.cpp menu.cpp file.cpp password.cpp)

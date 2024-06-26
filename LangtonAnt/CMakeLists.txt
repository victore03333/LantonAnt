cmake_minimum_required(VERSION 3.28)
project(LangtonAnt)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS graphics audio REQUIRED)
add_executable(LangtonAnt main.cpp
        VLangtonAnt.cpp
        VLangtonAnt.h)
target_link_libraries(LangtonAnt sfml-graphics sfml-audio)

cmake_minimum_required(VERSION 3.5)
project(main)

find_package(yaml-cpp)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_SOURCES
        main.cpp
        yaml_parser.cpp
        yaml_parser.h
        map.cpp
        map.h
)

add_executable(main
            ${PROJECT_SOURCES}
        )

target_link_libraries(main ${YAML_CPP_LIBRARIES})
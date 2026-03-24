cmake_minimum_required(VERSION 3.10.0)
project(Farmomatica VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
set(ALL_SOURCES ${SOURCES} ${HEADERS})

add_executable(Farmomatica ${ALL_SOURCES})
target_include_directories(Farmomatica PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(Farmomatica PRIVATE raylib glfw spdlog::spdlog)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    add_custom_target(
        copy_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink
                "${CMAKE_BINARY_DIR}/compile_commands.json"
                "${CMAKE_SOURCE_DIR}/compile_commands.json"
        DEPENDS "${CMAKE_BINARY_DIR}/compile_commands.json"
        COMMENT "Creating symlink for compile_commands.json in source dir"
    )
endif()

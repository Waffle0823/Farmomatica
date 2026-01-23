cmake_minimum_required(VERSION 3.10.0)
project(Farmomatica VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

add_executable(Farmomatica src/main.cpp)
target_link_libraries(Farmomatica PRIVATE raylib)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    set(COMPILE_COMMANDS_SRC
        "${CMAKE_BINARY_DIR}/compile_commands.json")
    set(COMPILE_COMMANDS_DST
        "${CMAKE_SOURCE_DIR}/compile_commands.json")

    if (EXISTS "${COMPILE_COMMANDS_SRC}")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink
                    "${COMPILE_COMMANDS_SRC}"
                    "${COMPILE_COMMANDS_DST}"
        )
    endif()
endif()
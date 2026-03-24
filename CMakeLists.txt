cmake_minimum_required(VERSION 3.10.0)
project(Farmomatica VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

option(SUPPORT_VULKAN_BACKEND "Enable Vulkan backend" ON)
option(SUPPORT_GLFW "Enable GLFW" ON)
option(SUPPORT_GLSL_PARSER "Enable GLSL parser" ON)

# TODO: Migrate to vcpkg when raygpu is available there
FetchContent_Declare(
    raygpu_git
    GIT_REPOSITORY https://github.com/manuel5975p/raygpu.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raygpu_git)

find_package(spdlog REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
set(ALL_SOURCES ${SOURCES} ${HEADERS})

add_executable(Farmomatica ${ALL_SOURCES})
target_include_directories(Farmomatica PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(Farmomatica PRIVATE raygpu spdlog::spdlog)

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

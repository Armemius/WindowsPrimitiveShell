cmake_minimum_required(VERSION 3.25)

project(
        PrimitiveWindowsShell
        VERSION 1.0.0
        DESCRIPTION "Primitive Windows shell"
        LANGUAGES C
)

include(cmake/compile_options.cmake)

add_subdirectory(apps)
add_subdirectory(src)

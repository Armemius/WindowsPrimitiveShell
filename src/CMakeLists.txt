file(GLOB_RECURSE SHELL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/shell/*.h")
file(GLOB_RECURSE SHELL_LIB_SRC CONFIGURE_DEPENDS "shell/*.c")
add_library(shell-utils ${SHELL_LIB_SRC} ${SHELL_HEADER_LIST})
target_include_directories(shell-utils PUBLIC "${PROJECT_SOURCE_DIR}/include")

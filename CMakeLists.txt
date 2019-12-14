cmake_minimum_required(VERSION 3.0.0)
project(CS31106 C)
project(CS31106 VERSION 0.1.0)

include(CTest)
enable_testing()

aux_source_directory(. DIR_SRCS)
add_subdirectory(utils)

add_executable(CS31106 ${DIR_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(CS31106 Utils)
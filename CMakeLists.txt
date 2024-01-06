# project setup
project(scriptRunner)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_VERBOSE_MAKEFILE OFF)

# cmake the library subdirectory
add_subdirectory(ScriptRunner/src/lib)

# create the binary for the scriptRunner
add_executable(scriptRunner ScriptRunner/src/scriptRunner.c)

target_link_libraries(scriptRunner PRIVATE scriptRunnerlibrary)

include_directories(scriptRunner PRIVATE ScriptRunner/src/lib/)

# install scriptRunner
install(TARGETS scriptRunner DESTINATION /usr/local/bin/)

# uninstall scriptRunner
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

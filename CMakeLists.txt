project(android-puzzle-server)
cmake_minimum_required(VERSION 3.9.4)

# if (CMAKE_CXX_COMPLIER_VERSION VERSION_LESS 6.0)
#     message(FATAL_ERROR "Insufficient gcc version, need 6.0 or higher")
# endif()

set(CMAKE_BUILD_TYPE Debug)

set(PUZZLE_SERVER_TARGET PuzzleServer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -std=c++11 -pthread")

SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Cmake control options
##########################################
option(BUILD_ENTRY "Build the Judge System main entry" ON)
############################################################

# header directories
###########################################################
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ext/fmt/include")

IF (APPLE)
  include_directories("/usr/local/include/mysql")
  include_directories("/usr/local/include/mysql++")
ELSEIF (UNIX)
  include_directories("/usr/include/mysql")
  include_directories("/usr/include/mysql++")
ENDIF ()

##############################################################

# source files
#############################################################
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp")
file(GLOB ENTRY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
################################################################

# Necessary libraries
#############################################################
find_package(Boost 1.65 COMPONENTS system REQUIRED)

# Force to build Release version
set(CMAKE_BUILD_TYPE_SAVED "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE Release)

####################################################################

if (BUILD_ENTRY)
  add_executable(${PUZZLE_SERVER_TARGET} ${SOURCE_FILES} ${ENTRY_FILE})
  set_target_properties(${PUZZLE_SERVER_TARGET}
    PROPERTIES
    # ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    # LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    CXX_STANDARD 14
    )
  target_link_libraries(${PUZZLE_SERVER_TARGET}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    mysqlclient
    mysqlpp
    ssl
    crypto
    )
  install(TARGETS ${PUZZLE_SERVER_TARGET} RUNTIME DESTINATION bin)
endif()


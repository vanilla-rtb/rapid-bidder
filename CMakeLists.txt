# -*- cmake -*-

cmake_minimum_required(VERSION 3.1)


project(rapid-bidder)

if(WIN32)
else(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -ggdb")
endif(WIN32)

set(CMAKE_CXX_STANDARD 14)
set(ENABLE_REDISCLIENT TRUE)
set(SUBMODULES_DIR "submodules")

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
SET ( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
ENDIF()
message("CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}")

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

IF (UNIX AND NOT APPLE)
    SET(CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/../lib64")
ELSE (LINUX)
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/lib64")
ENDIF (LINUX)

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/etc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

set(REQUIRED_BOOST_LIBRARIES)
list(APPEND REQUIRED_BOOST_LIBRARIES "log" "program_options" "system" "serialization" "date_time")
set(Boost_USE_MULTITHREADED ON)
find_package(Boost
             COMPONENTS "${REQUIRED_BOOST_LIBRARIES}"
             REQUIRED
            )


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


add_definitions(-DBOOST_LOG_DYN_LINK -DBOOST_PROGRAM_OPTIONS_DYN_LINK)


if (WIN32)
    link_directories(${Boost_LIBRARY_DIRS})
endif(WIN32)


add_subdirectory(framework)

if(ENABLE_REDISCLIENT)
    include(ExternalProject)

    ExternalProject_Add(redisclient
        SOURCE_DIR ${SUBMODULES_DIR}/redisclient
        PREFIX ${SUBMODULES_DIR}/redisclient
        INSTALL_COMMAND ""
    )
endif()

add_subdirectory(exchange_server)
add_subdirectory(bidders)
add_subdirectory(loaders)
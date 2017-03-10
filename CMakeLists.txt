# -*- cmake -*-

cmake_minimum_required(VERSION 3.1)

if(WIN32)
else(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -ggdb")
endif(WIN32)

set(CMAKE_CXX_STANDARD 14)

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

## Configuring vanilla-rtb/dsp/exchange_server
include_directories("${PROJECT_SOURCE_DIR}"
                    "${PROJECT_SOURCE_DIR}/framework/"
                    "${PROJECT_SOURCE_DIR}/framework/rtb"
                    "${PROJECT_SOURCE_DIR}/framework/jsonv/include"
                   )


add_definitions(-DBOOST_LOG_DYN_LINK -DBOOST_PROGRAM_OPTIONS_DYN_LINK)


if (WIN32)
    link_directories(${Boost_LIBRARY_DIRS})
endif(WIN32)


add_subdirectory(framework)
add_subdirectory(exchange_server)
add_subdirectory(bidders)
add_subdirectory(loaders)


cmake_minimum_required(VERSION 3.1)

## Configuring to include framework 
include_directories("${PROJECT_SOURCE_DIR}"
                    "${PROJECT_SOURCE_DIR}/framework"
                    "${PROJECT_SOURCE_DIR}/framework/jsonv/include"
                   )

add_executable(
    multi_bidder_service
    multi_bidder_service.cpp
)
add_executable(
    http_bidder
    http_bidder.cpp
)

if (WIN32) 
    target_compile_definitions(multi_bidder_service PRIVATE  JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(http_bidder PRIVATE  JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(jsonv PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
endif(WIN32)

if ( NOT WIN32)
set(RT_LIB rt)
endif(NOT WIN32)

target_link_libraries(
        multi_bidder_service
        crud_service
        vanilla_rtb
        jsonv
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${RT_LIB}
        )

target_link_libraries(
        http_bidder
        crud_service
        vanilla_rtb
        jsonv
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${RT_LIB}
        )


cmake_minimum_required(VERSION 3.1)

add_executable(
    multi_bidder
    multi_bidder.cpp
)
add_executable(
    http_bidder
    http_bidder.cpp
)

if (WIN32) 
    target_compile_definitions(multi_bidder PRIVATE  JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(http_bidder PRIVATE  JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(jsonv PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
endif(WIN32)

target_link_libraries(
        multi_bidder
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


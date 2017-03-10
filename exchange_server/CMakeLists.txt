cmake_minimum_required(VERSION 3.1)

add_executable(
        exchange_server
        exchange_server.cpp
        )

add_executable(
        multi_bidder_exchange_server
        multi_bidder_exchange_server.cpp
        )

if (WIN32)
    target_compile_definitions(exchange_server PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(multi_bidder_exchange_server PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1 _CRT_NONSTDC_NO_DEPRECATE )
    target_compile_definitions(jsonv PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
endif(WIN32)

find_package (Threads)


target_link_libraries(
        exchange_server
        crud_service
        vanilla_rtb
        jsonv
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )

if ( NOT WIN32)
set(RT_LIB rt)
endif(NOT WIN32)


target_link_libraries(
        multi_bidder_exchange_server
        vanilla_rtb
        jsonv
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${RT_LIB}
        )


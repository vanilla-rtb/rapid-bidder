cmake_minimum_required(VERSION 3.1)


include_directories(
                   "${PROJECT_SOURCE_DIR}"
                   "${PROJECT_SOURCE_DIR}/bidder"
                   )

add_executable(
    cache_loader_service
    cache_loader_service.cpp
)


if (WIN32)
    target_compile_definitions(cache_loader_service PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
    target_compile_definitions(jsonv PRIVATE JSON_SO=1 _LIB JSON_COMPILING=1)
endif(WIN32)

target_link_libraries(
    cache_loader_service
    crud_service
    vanilla_rtb
    jsonv
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${RT_LIB}
)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(ammo)
option(BUILD_TESTS "Build tests" OFF)
add_executable(ammo ${CMAKE_CURRENT_SOURCE_DIR}/munition/munition.cpp)


install(TARGETS ammo RUNTIME DESTINATION ammo)
if (BUILD_TESTS)
    enable_testing()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/munition)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
    add_subdirectory(modules/gtest)
    add_executable(t_ammo ${CMAKE_CURRENT_SOURCE_DIR}/test_ammo.cpp)
    target_link_libraries(t_ammo gtest_main gtest gmock)
    add_test(NAME t_ammo COMMAND t_ammo)
endif()

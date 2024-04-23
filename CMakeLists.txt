cmake_minimum_required(VERSION 3.27)
project(proj_trad_block)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj_trad_block
        main.cpp
        OrderBookEntry.cpp
        OrderBookEntry.h
        WaizMain.cpp
        WaizMain.h)

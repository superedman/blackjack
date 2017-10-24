cmake_minimum_required(VERSION 3.8)
project(blackjack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp card.h)
add_executable(blackjack ${SOURCE_FILES})
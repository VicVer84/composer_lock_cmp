cmake_minimum_required(VERSION 3.10)

project(composer_lock_cmp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(composer_lock_cmp
    ${CMAKE_SOURCE_DIR}/src/composer_lock_cmp.cpp
	${CMAKE_SOURCE_DIR}/src/composer_lock_cmp.h
	${CMAKE_SOURCE_DIR}/src/json.hpp
)
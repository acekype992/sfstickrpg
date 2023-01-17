cmake_minimum_required(VERSION 3.23)

project(SFStickRPG)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(extlib/)
add_subdirectory(src/)

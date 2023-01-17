#!/bin/bash

BUILD_TYPE=$1
GENERATOR=Ninja
CCOMPILER=/usr/bin/gcc
CXXCOMPILER=/usr/bin/g++

if [ -z "${BUILD_TYPE}" ]; then
    BUILD_TYPE=release
fi

if [[ $BUILD_TYPE != "release"  &&  $BUILD_TYPE != "debug" ]]; then
    echo "usage : configure <BUILD_TYPE>"
    echo "BUILD_TYPE :"
    echo -e "\tdebug"
    echo -e "\trelease"
    exit
fi


if [[ ! -d build/${BUILD_TYPE,,} ]]; then
    echo "No build directory found."
    echo "Run the configure script before make."
    exit
else
    if [ -z "$(ls -p build/${BUILD_TYPE,,} | grep -v /)" ]; then
        echo "Build directory is empty."
        echo "Run the configure script before make."
        exit
    fi
fi

if [ -f build/${BUILD_TYPE,,}/build.ninja ]; then
    ninja -C build/${BUILD_TYPE,,}/
else
    echo "build.ninja no found in build folder."
    echo "Run the configure script."
    exit
fi

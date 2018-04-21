cmake_minimum_required(VERSION 3.2)

## Use the variable PROJECT_NAME for changing the target name.
set( PROJECT_NAME "structures" )

## Set our project name.
project( ${PROJECT_NAME} )

## Use all the *.cpp files we find under ./src for the project.
file( GLOB_RECURSE SRCS "${PROJECT_SOURCE_DIR}/src/*.c*" )
include_directories( "${PROJECT_SOURCE_DIR}/src/" )

## Compiler options.
set( CMAKE_CXX_FLAGS "-std=c++03 -masm=intel -Wall -Wextra" )

## Define the executable
add_executable( ${PROJECT_NAME} ${SRCS} )

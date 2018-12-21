cmake_minimum_required(VERSION 3.13)
project(CountdownNumberSearch)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_FIND_LIBRARY_SUFFIXES .dll .lib .a .so)
SET(BUILD_SHARED_LIBS OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(CountdownNumberSearch
        main.cpp
        headers/SimpleMathOps.h
        sources/SimpleMathOps.cpp
        sources/PermutationCalculator.cpp
        headers/PermutationCalculator.h
        sources/PermutationResult.cpp
        headers/PermutationResult.h
        sources/VectorUtil.cpp
        headers/VectorUtil.h
        headers/CountdownAliases.h
        sources/ExpressionEvaluator.cpp
        headers/ExpressionEvaluator.h
        sources/ResultsGenerator.cpp
        headers/ResultsGenerator.h
        headers/util/CMathParser.h
        sources/util/CMathParser.cpp
        )
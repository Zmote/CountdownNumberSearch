cmake_minimum_required(VERSION 3.13)
project(CountdownNumberSearch)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_FIND_LIBRARY_SUFFIXES .dll .lib .a .so)
SET(BUILD_SHARED_LIBS OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(Boost_INCLUDE_DIR D:/boost_1_63_0)
set(Boost_LIBRARY_DIR D:/boost_1_63_0/stage/lib)
#Extend with COMPONENT [component names..] REQUIRED
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(CountdownNumberSearch
        main.cpp
        sources/PermutationCalculator.cpp
        headers/PermutationCalculator.h
        sources/types/EvaluationResult.cpp
        headers/types/EvaluationResult.h
        sources/VectorUtil.cpp
        headers/VectorUtil.h
        headers/CountdownAliases.h
        sources/ExpressionEvaluator.cpp
        headers/ExpressionEvaluator.h
        sources/ResultsGenerator.cpp
        headers/ResultsGenerator.h
        headers/util/CMathParser.h
        sources/util/CMathParser.cpp
        headers/types/Permutation.h sources/types/PermutationList.cpp headers/types/PermutationList.h headers/typetraits/CountdownTraits.h)

# Uncomment if using linked libs of boost
#TARGET_LINK_LIBRARIES(CountdownNumberSearch LINK_PUBLIC ${Boost_LIBRARIES})
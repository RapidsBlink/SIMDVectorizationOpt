cmake_minimum_required(VERSION 3.6)
project(SIMDVectorization)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}) # To allow CMake to locate our Find*.cmake files
#set(CMAKE_BUILD_TYPE "Release")
# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(enableLOG "enable loging" ON)

add_compile_options(-O3 -Wall)

if (enableLOG)
    add_definitions(-DUSE_LOG)
endif ()

include(FindSSE)
if (AVX2_FOUND)
    message("found AVX2")
    add_compile_options(-mavx2)
elseif (AVX_FOUND)
    message("found AVX")
    add_compile_options(-mavx)
elseif (SSE4_1_FOUND)
    message("found sse4.1")
    add_compile_options(-msse4.1)
elseif (SSE2_FOUND)
    message("found sse2")
    add_compile_options(-msse2)
endif ()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-mpopcnt" COMPILER_OPT_POPCNT_SUPPORTED)
if (COMPILER_OPT_POPCNT_SUPPORTED)
    add_compile_options(-mpopcnt)
endif ()

find_package(Threads)
find_package(Tcmalloc)
if (Tcmalloc_FOUND)
    include_directories(${Tcmalloc_INCLUDE_DIR})
    set(TCMALLOC_LIBS ${Tcmalloc_LIBRARIES})
endif ()

#find_package(TBB REQUIRED)
#include_directories(${TBB_INCLUDE_DIRS})

add_subdirectory(src/playground)

find_package(Snappy)
find_package(LZ4)

find_package(OpenMP)

if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

if (AVX2_FOUND)
    message(avx2)
    set(AVX2_BASE64_FILES ../fast_base64/fastavxbase64.c ../fast_base64/klompavxbase64.c)
endif ()

if (AVX2_FOUND)
    add_executable(test_instrinsics ../utils/log.cpp ../fast_base64/chromiumbase64.c
            ../fast_base64/fastavxbase64.c ../fast_base64/klompavxbase64.c test_instrinsics.cpp)
endif ()

add_executable(test_serialization test_serialization.cpp ../utils/serialization.cpp ../utils/serialization.h
        ../utils/log.cpp ../fast_base64/chromiumbase64.c ${AVX2_BASE64_FILES})

add_executable(test_split_avx test_split.cpp ../fast_tokenizer/tokenizer.cpp ../utils/utils.cpp ../utils/log.cpp)
target_compile_options(test_split_avx PRIVATE -O2)

if (AVX2_FOUND)
    add_executable(test_avx2_instrinsics test_avx2_instrinsics.cpp ../utils/log.cpp)
    target_compile_options(test_avx2_instrinsics PRIVATE -march=native)
endif ()
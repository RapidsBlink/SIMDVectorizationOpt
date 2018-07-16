find_package(Snappy)
find_package(LZ4)

# openmp for fast generating a huge array
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

if (AVX2_FOUND)
    message(avx2)
    # 1st: set avx2 base64 files
    set(AVX2_BASE64_FILES ../fast_base64/fastavxbase64.c ../fast_base64/klompavxbase64.c)

    # 2nd: test instrinsics
    add_executable(test_instrinsics ../utils/log.cpp ../fast_base64/chromiumbase64.c
            ../fast_base64/fastavxbase64.c ../fast_base64/klompavxbase64.c test_instrinsics.cpp)

    # 3rd: test instrinsics another
    add_executable(test_avx2_instrinsics test_avx2_instrinsics.cpp ../utils/log.cpp)
    target_compile_options(test_avx2_instrinsics PRIVATE -march=native)
endif ()

# Benchmarking Tokenizing
add_executable(test_split_avx test_split.cpp ../fast_tokenizer/tokenizer.cpp ../utils/utils.cpp ../utils/log.cpp)
target_compile_options(test_split_avx PRIVATE -O2)

# Benchmarking Serialization/Deserialization
set(SERIALIZATION_TEST_FILES test_serialization.cpp ../utils/log.cpp
        ../utils/serialization.cpp ../utils/serialization.h
        ../fast_base64/chromiumbase64.c
        ../naive_base64/naive_base64.cpp ../naive_base64/naive_base64.h)

# the macro for generating the benchmarking execs
macro(InitExecList exec_suffix extra_define)
    add_executable(naive_comp_${exec_suffix} ${SERIALIZATION_TEST_FILES})
    target_compile_definitions(naive_comp_${exec_suffix} PRIVATE -DDISABLE_AVX2=1 -DNAIVE_COMP=1 ${extra_define})

    add_executable(naive_lookup_${exec_suffix} ${SERIALIZATION_TEST_FILES})
    target_compile_definitions(naive_lookup_${exec_suffix} PRIVATE -DDISABLE_AVX2=1 -DNAIVE_LOOKUP=1 ${extra_define})

    add_executable(chromium_${exec_suffix} ${SERIALIZATION_TEST_FILES})
    target_compile_definitions(chromium_${exec_suffix} PRIVATE -DDISABLE_AVX2=1 ${extra_define})

    if (AVX2_FOUND)
        add_executable(avx2_chromium_${exec_suffix} ${SERIALIZATION_TEST_FILES} ${AVX2_BASE64_FILES})
        target_compile_definitions(avx2_chromium_${exec_suffix} PRIVATE ${extra_define})
    endif ()
endmacro()

InitExecList(enable_deserialize -DENABLE_DESERIALIZE=1)
InitExecList(disable_deserialize "")

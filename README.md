# SIMD Vectorization Demo

intel intrinsics guide: see https://software.intel.com/sites/landingpage/IntrinsicsGuide/

bechmarking CPU info: see [python_playground](python_playground), using single-thread

## Tokenizing

/ | type
--- | ---
input  | form body
output | dubbo package

algorithms | elapsed time
--- | ---
serial transform time | 380 ms
sse4 transform time | 240 ms
avx2 transform time | 90 ms

* workaround for `__tzcnt_u32` (requiring bmi)  in sse4

```cpp
inline int __tzcnt_u32_using_popcnt_cmpgt(unsigned int x) {
    int ret_cnt = 0;
    int half_bits = x & (0xff);
    if (half_bits == 0) {
        half_bits = (x >> 8) & (0xff);
        ret_cnt = 8;
    }

    __m128i pivot_u = _mm_set1_epi16(half_bits);
    __m128i inspected_ele = _mm_set_epi16(0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1);
    __m128i trunc_pivot_u = _mm_and_si128(pivot_u, inspected_ele);

    __m128i pivot_new = _mm_set1_epi16(0);
    __m128i cmp_res = _mm_cmpeq_epi16(trunc_pivot_u, pivot_new);

    int mask = _mm_movemask_epi8(cmp_res); // 16 bits
    ret_cnt += _mm_popcnt_u32(mask) >> 1;
    return ret_cnt;
}
```

* idea: advance with simd cmp and tzcnt

```cpp
        // 1st: advance fo find first '='
        while (true) {
            __m128i pivot_u = _mm_set1_epi8('=');
            __m128i inspected_ele = _mm_loadu_si128((__m128i *) (str + i));
            __m128i cmp_res = _mm_cmpeq_epi8(pivot_u, inspected_ele);
            int mask = _mm_movemask_epi8(cmp_res); // 16 bits

            int advance = (mask == 0 ? 16 : __tzcnt_u32_using_popcnt_cmpgt(mask));
            i += advance;
            if (advance < 16) { break; }
        }
        off[next] = i;
        next++;
```

* details: see [src/fast_tokenizer/tokenizer.cpp](src/fast_tokenizer/tokenizer.cpp), [src/playground/test_split.cpp](src/playground/test_split.cpp)

## Base64 Decoding/Encoding (i.e, Serialization/Deserialization)

* base64 encoding includes 1) unpacking and 2) ascii translation (to)

* base64 decoding includes 1) ascii translation (from) and 2) packing

* the translation table

base64 | ascii | offset (diff)
---    | ---   | ---
0-25   | (65-90)  0x41-0x5a | 65
26-51  | (97-122) 0x61-0x7a | 71
52-61  | (48-57)  0x40-0x49 | -4
62     | '+' (43) 0x2b      | -19
63     | '/' (47) 0x2f      | -16
others | invalid            | invalid

### Benchmark

* implementations

benchmark main file: [src/playground/test_serialization.cpp](src/playground/test_serialization.cpp)

algorithms | link
--- | ---
naive-comp   | [src/naive_base64/naive_base64.cpp](src/naive_base64/naive_base64.cpp)
naive-lookup | [src/naive_base64/naive_base64.cpp](src/naive_base64/naive_base64.cpp)
chromium     | [src/fast_base64/chromiumbase64.c](src/fast_base64/chromiumbase64.c)
fast-avx2    | [src/fast_base64/fastavxbase64.c](src/fast_base64/fastavxbase64.c)

* measure: we report TPS (throughput including both serialization and deserialization time)

algorithms | idea
--- | ---
naive-comp   | ascii-base64 translation using computations
naive-lookup | ascii-base64 translation using two look-up tables
chromium     | use separate lookup tables for saving some computations
fast-avx2    | apply avx2, and serial fallback using chromium

* message len 80

algorithms | TPS
--- | ---
naive-comp   | 151.151991 MB/s
naive-lookup | 406.132152 MB/s
chromium     | 406.546169 MB/s
fast-avx2    | 570.026750 MB/s

* message len 50

algorithms | TPS
--- | ---
naive-comp   | 117.456860 MB/s
naive-lookup | 325.850751 MB/s
chromium     | 331.729820 MB/s
fast-avx2    | 391.287010 MB/s

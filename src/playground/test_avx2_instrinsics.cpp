//
// Created by yche on 7/15/18.
//

#include <x86intrin.h>
#include <cstdint>

#include "../utils/log.h"

void test_srli_epi32_as_unit() {
    __m256i integer = _mm256_set1_epi32(0xfeeeeeef);
    __m256i res = _mm256_srli_epi32(integer, 4);
    int32_t ints[8];

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(ints), res);
    for (int32_t int_my: ints) {
        log_info("my int: 0x%x", (int64_t) int_my & 0xffffffffL);
    }
}

int main() {
    // regard this as two hash tables for two 128-bit simd lanes
    __m256i high_shuffule_table = _mm256_setr_epi8(
            0x10, 0x10, 0x01, 0x02, 0x04, 0x08, 0x04, 0x08, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x01, 0x02, 0x04, 0x08, 0x04, 0x08, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
    );

    __m256i table_values = _mm256_shuffle_epi8(high_shuffule_table, _mm256_set1_epi8(3));
    uint8_t values[32];
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(values), table_values);
    for (uint8_t v: values) {
        log_info("v: 0x%x", v & 0xff);
    }
}
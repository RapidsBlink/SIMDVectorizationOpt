//
// Created by yche on 7/17/18.
//
#include <x86intrin.h>
#include "../utils/log.h"

inline int __tzcnt_u32_using_popcnt_cmpeq(unsigned int x) {
    int ret_cnt = 0;
    int half_bits = x & (0xff);
    if (half_bits == 0) {
        half_bits = (x >> 8) & (0xff);
        ret_cnt = 8;
    }

    __m128i pivot_u = _mm_set1_epi16(half_bits);
    __m128i inspected_ele = _mm_set_epi16(
            0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1);
    __m128i trunc_pivot_u = _mm_and_si128(pivot_u, inspected_ele);

    __m128i pivot_new = _mm_set1_epi16(0);
    __m128i cmp_res = _mm_cmpeq_epi16(trunc_pivot_u, pivot_new);

    int mask = _mm_movemask_epi8(cmp_res); // 16 bits
    ret_cnt += _mm_popcnt_u32(mask) >> 1;
    return ret_cnt;
}

int main() {
    const char *str = "interface=com.al";
    __m128i pivot_u = _mm_set1_epi8('=');
    __m128i inspected_ele = _mm_loadu_si128((__m128i *) (str));
    __m128i cmp_res = _mm_cmpeq_epi8(pivot_u, inspected_ele);
    int mask = _mm_movemask_epi8(cmp_res); // 16 bits

    log_info("mask: 0x%x", mask & 0xffff);
    int advance = (mask == 0 ? 16 : __tzcnt_u32_using_popcnt_cmpeq(mask));
    log_info("advance: %d", advance);
}

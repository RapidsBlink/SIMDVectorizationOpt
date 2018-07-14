#include <cstdio>
#include <cassert>
#include <cstring>

#include "emmintrin.h"

#include "../fast_base64/fastavxbase64.h"
#include "../fast_base64/klompavxbase64.h"

void klomp_avx2_checkExample(const char *source, const char *coded) {
    printf("klomp avx2 codec check.\n");
    size_t len;
    size_t codedlen;

    char *dest1 = (char *) malloc(chromium_base64_encode_len(strlen(source)));

    klomp_avx2_base64_encode(source, strlen(source), dest1, &codedlen);
    assert(strncmp(dest1, coded, codedlen) == 0);
    char *dest2 = (char *) malloc(chromium_base64_decode_len(codedlen));
    klomp_avx2_base64_decode(coded, codedlen, dest2, &len);
    assert(len == strlen(source));
    assert(strncmp(dest2, source, strlen(source)) == 0);
    char *dest3 = (char *) malloc(chromium_base64_decode_len(codedlen));
    klomp_avx2_base64_decode(dest1, codedlen, dest3, &len);
    assert(len == strlen(source));
    assert(strncmp(dest3, source, strlen(source)) == 0);
    free(dest1);
    free(dest2);
    free(dest3);
}


void fast_avx2_checkExample(const char *source, const char *coded) {
    printf("fast_avx2 codec check.\n");
    size_t len;
    size_t codedlen;

    char *dest1 = (char *) malloc(chromium_base64_encode_len(strlen(source)));
    codedlen = fast_avx2_base64_encode(dest1, source, strlen(source));
    assert(strncmp(dest1, coded, codedlen) == 0);
    char *dest2 = (char *) malloc(chromium_base64_decode_len(codedlen));
    len = fast_avx2_base64_decode(dest2, coded, codedlen);
    assert(len == strlen(source));
    assert(strncmp(dest2, source, strlen(source)) == 0);
    char *dest3 = (char *) malloc(chromium_base64_decode_len(codedlen));
    len = fast_avx2_base64_decode(dest3, dest1, codedlen);
    assert(len == strlen(source));
    assert(strncmp(dest3, source, strlen(source)) == 0);
    free(dest1);
    free(dest2);
    free(dest3);
}

int main() {
    // from Wikipedia page
    const char *wikipediasource = "Man is distinguished, not only by his reason, but by this singular passion from \
other animals, which is a lust of the mind, that by a perseverance of delight \
in the continued and indefatigable generation of knowledge, exceeds the short \
vehemence of any carnal pleasure.";
    const char *wikipediacoded = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz\
IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg\
dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu\
dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo\
ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";

    // from https://gobyexample.com/base64-encoding
    const char *gosource = "abc123!?$*&()'-=@~";
    const char *gocoded = "YWJjMTIzIT8kKiYoKSctPUB+";

    // from https://www.tutorialspoint.com/java8/java8_base64.htm
    const char *tutosource = "TutorialsPoint?java8";
    const char *tutocoded = "VHV0b3JpYWxzUG9pbnQ/amF2YTg=";

    klomp_avx2_checkExample(wikipediasource, wikipediacoded);
    klomp_avx2_checkExample(gosource, gocoded);
    klomp_avx2_checkExample(tutosource, tutocoded);

    fast_avx2_checkExample(wikipediasource, wikipediacoded);
    fast_avx2_checkExample(gosource, gocoded);
    fast_avx2_checkExample(tutosource, tutocoded);
}

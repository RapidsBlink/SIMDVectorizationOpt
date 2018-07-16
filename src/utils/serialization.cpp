#include <cstdint>
#include <cstring>

#include "serialization.h"
#include "../fast_base64/fastavxbase64.h"
#include "../naive_base64/naive_base64.h"
#include "log.h"

#if defined(NAIVE_LOOKUP)
#define SERIAL_DECODE naive_base64_decode
#define SERIAL_ENCODE naive_base64_encode
#elif defined(NAIVE_COMP)
#define SERIAL_DECODE naive_base64_decode_comp
#define SERIAL_ENCODE naive_base64_encode_comp
#else
#define SERIAL_DECODE chromium_base64_decode
#define SERIAL_ENCODE chromium_base64_encode
#endif

#if defined(DISABLE_AVX2)
#undef __AVX2__
#endif

#define BINARY_PART_LEN (8u)

/*
 * output:
 * part1: varying_len_byte (1 or 2),
 * part2: bytes for packed base64 bytes (3x),
 * part3: left_char_byte namely serialized[estimated_length] (1),
 * part4: memcpy bytes (BINARY_PART_LEN + serialized[estimated_length])
 */

int serialize_base64_decoding_general(uint8_t *message, uint16_t len, uint8_t *serialized) {
    // serialize_len: 4x
    size_t chunk_num = (len - BINARY_PART_LEN) / 4;
    size_t serialize_len = chunk_num * 4;
    size_t estimated_length = 3 * chunk_num;

    // 1st: varying bytes interpretation: length of base64 packed values
    if (estimated_length < 128) {
        serialized[0] = static_cast<uint8_t>(estimated_length);
        serialized += 1;
    } else {
        serialized[0] = static_cast<uint8_t>((estimated_length >> 7u) | 0x80); // assume < 32767
        serialized[1] = static_cast<uint8_t>(estimated_length & (uint8_t) 0x7f);
        serialized += 2;
    }

    // 2nd: left base64 char number
    serialized[estimated_length] = static_cast<uint8_t>((len - BINARY_PART_LEN) % 4u);
    // 3rd: copy left chars and fixed binary part
    int copy_length = BINARY_PART_LEN + serialized[estimated_length];
    memcpy(serialized + estimated_length + 1, message + serialize_len, copy_length);

#ifdef __AVX2__
    fast_avx2_base64_decode(reinterpret_cast<char *>(serialized), reinterpret_cast<const char *>(message),
                            serialize_len);
#else
    SERIAL_DECODE(reinterpret_cast<char *>(serialized), reinterpret_cast<const char *>(message), serialize_len);

#endif
    return estimated_length + copy_length + (serialize_len < 128 ? 1 : 2);
}

uint8_t *deserialize_base64_encoding_general(const uint8_t *serialized, uint16_t total_serialized_len, int &len) {
    // 1st: get the length of varying part
    uint16_t varying_byte_len;

    if ((serialized[0] & 0x80u) == 0) {
        varying_byte_len = serialized[0];
        serialized += 1;
    } else {
        varying_byte_len = static_cast<uint16_t>(((serialized[0] & 0x7fu) << 7u) + serialized[1]);
        serialized += 2;
    }

    int left_bytes = BINARY_PART_LEN + serialized[varying_byte_len];
    auto *deserialized = new uint8_t[varying_byte_len / 3 * 4 + left_bytes];
    // 2nd: base64 part
#ifdef __AVX2__
    size_t length = fast_avx2_base64_encode(reinterpret_cast<char *>(deserialized),
                                            reinterpret_cast<const char *>(serialized), varying_byte_len);
#else
    size_t length = SERIAL_ENCODE(reinterpret_cast<char *>(deserialized),
                                  reinterpret_cast<const char *>(serialized), varying_byte_len);

#endif

    // 3rd: fixed part and left chars
    memcpy(deserialized + length, serialized + varying_byte_len + 1, left_bytes);
    // 4th: assign the len
    len = length + left_bytes;
    return deserialized;
}

uint8_t *deserialize_base64_encoding(const uint8_t *serialized, uint16_t total_serialized_len, int &len) {
    auto serialize_len = total_serialized_len - FIXED_PART_LEN - 1;
    auto *deserialized = new uint8_t[total_serialized_len / 3 * 4 + 16];

#ifdef __AVX2__
    size_t length = fast_avx2_base64_encode(reinterpret_cast<char *>(deserialized),
                                            reinterpret_cast<const char *>(serialized), serialize_len);
#else
    size_t length = SERIAL_ENCODE(reinterpret_cast<char *>(deserialized),
                                  reinterpret_cast<const char *>(serialized), serialize_len);

#endif
    memcpy(deserialized + length - serialized[total_serialized_len - 1], serialized + serialize_len, FIXED_PART_LEN);
    len = length - serialized[total_serialized_len - 1] + FIXED_PART_LEN;
    return deserialized;
}

int serialize_base64_decoding(uint8_t *message, uint16_t len, uint8_t *serialized) {
    auto serialize_len = len - FIXED_PART_LEN;
    int padding_chars = (4 - serialize_len % 4) % 4;
    uint8_t *buf = message;

    size_t estimated_length = 3 * (serialize_len / 4 + (serialize_len % 4 == 0 ? 0 : 1));
    memcpy(serialized + estimated_length, message + serialize_len, FIXED_PART_LEN);
    // attention: add padding chars, assume following chars enough >= 3
    memcpy(message + serialize_len, "BLINK", padding_chars);

#ifdef __AVX2__
    fast_avx2_base64_decode(reinterpret_cast<char *>(serialized),
                                            reinterpret_cast<const char *>(buf),
                                            serialize_len + padding_chars);
#else

    SERIAL_DECODE(reinterpret_cast<char *>(serialized),
                  reinterpret_cast<const char *>(buf),
                  serialize_len + padding_chars);
#endif
    serialized[estimated_length + FIXED_PART_LEN] = padding_chars;
    return estimated_length + FIXED_PART_LEN + 1;
}

// Skip index =================================================================================================
int serialize_base64_decoding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized) {
    auto serialize_len = len - FIXED_PART_LEN;
    int padding_chars = (4 - serialize_len % 4) % 4;
    uint8_t *buf = message;

    size_t estimated_length = 3 * (serialize_len / 4 + (serialize_len % 4 == 0 ? 0 : 1));
    memcpy(serialized + estimated_length, message + serialize_len, BASE64_INFO_LEN);
    memcpy(serialized + estimated_length + BASE64_INFO_LEN, message + serialize_len + BASE64_INFO_LEN + INDEX_LEN,
           VARYING_VERIFY_LEN);
    // attention: add padding chars, assume following chars enough >= 3
    memcpy(message + serialize_len, "BLINK", padding_chars);

#ifdef __AVX2__
    fast_avx2_base64_decode(reinterpret_cast<char *>(serialized),
                                            reinterpret_cast<const char *>(buf),
                                            serialize_len + padding_chars);
#else

    SERIAL_DECODE(reinterpret_cast<char *>(serialized),
                  reinterpret_cast<const char *>(buf),
                  serialize_len + padding_chars);
#endif
    serialized[estimated_length + FIXED_PART_LEN - INDEX_LEN] = padding_chars;
    return estimated_length + FIXED_PART_LEN - INDEX_LEN + 1;
}

uint8_t *deserialize_base64_encoding_add_index(const uint8_t *serialized, uint16_t total_serialized_len,
                                               int &deserialized_len, int32_t idx) {
    auto serialize_len = total_serialized_len - (FIXED_PART_LEN - INDEX_LEN) - 1;
    auto *deserialized = new uint8_t[total_serialized_len / 3 * 4 + 16];

#ifdef __AVX2__
    size_t length = fast_avx2_base64_encode(reinterpret_cast<char *>(deserialized),
                                            reinterpret_cast<const char *>(serialized), serialize_len);
#else
    size_t length = SERIAL_ENCODE(reinterpret_cast<char *>(deserialized),
                                  reinterpret_cast<const char *>(serialized), serialize_len);

#endif
    size_t offset = length - serialized[total_serialized_len - 1];
    memcpy(deserialized + offset, serialized + serialize_len, BASE64_INFO_LEN);
    offset += BASE64_INFO_LEN;
    memcpy(deserialized + offset, &idx, sizeof(int32_t));
    offset += INDEX_LEN;
    memcpy(deserialized + offset, serialized + serialize_len + BASE64_INFO_LEN, VARYING_VERIFY_LEN);

    deserialized_len = length - serialized[total_serialized_len - 1] + FIXED_PART_LEN;
    return deserialized;
}

void deserialize_base64_encoding_add_index_in_place(const uint8_t *serialized, uint16_t total_serialized_len,
                                                    uint8_t *deserialized, int &deserialized_len, int32_t idx) {
    auto serialize_len = total_serialized_len - (FIXED_PART_LEN - INDEX_LEN) - 1;

#ifdef __AVX2__
    size_t length = fast_avx2_base64_encode(reinterpret_cast<char *>(deserialized),
                                            reinterpret_cast<const char *>(serialized), serialize_len);
#else
    size_t length = SERIAL_ENCODE(reinterpret_cast<char *>(deserialized),
                                  reinterpret_cast<const char *>(serialized), serialize_len);

#endif
    size_t offset = length - serialized[total_serialized_len - 1];
    memcpy(deserialized + offset, serialized + serialize_len, BASE64_INFO_LEN);
    offset += BASE64_INFO_LEN;
    memcpy(deserialized + offset, &idx, sizeof(int32_t));
    offset += INDEX_LEN;
    memcpy(deserialized + offset, serialized + serialize_len + BASE64_INFO_LEN, VARYING_VERIFY_LEN);

    deserialized_len = length - serialized[total_serialized_len - 1] + FIXED_PART_LEN;
}
// End of Skip index ========================================================================================

// ------------------------------- Begin of Base36 -------------------------------------------------------------
int serialize_base36_decoding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized) {
    auto serialize_len = len - FIXED_PART_LEN;
    int padding_chars = (4 - serialize_len % 4) % 4;
    uint8_t *buf = message;

    size_t estimated_length = 3 * (serialize_len / 4 + (serialize_len % 4 == 0 ? 0 : 1));
    memcpy(serialized + estimated_length, message + serialize_len, BASE64_INFO_LEN);
    memcpy(serialized + estimated_length + BASE64_INFO_LEN, message + serialize_len + BASE64_INFO_LEN + INDEX_LEN,
           VARYING_VERIFY_LEN);
    // attention: add padding chars, assume following chars enough >= 3
    memcpy(message + serialize_len, "BLINK", padding_chars);

#ifdef __AVX2__
    fast_avx2_base64_decode(reinterpret_cast<char *>(serialized),
                                            reinterpret_cast<const char *>(buf),
                                            serialize_len + padding_chars);
#else

    SERIAL_DECODE(reinterpret_cast<char *>(serialized),
                  reinterpret_cast<const char *>(buf),
                  serialize_len + padding_chars);
#endif
    return estimated_length + FIXED_PART_LEN - INDEX_LEN;
}

uint8_t *deserialize_base36_encoding_add_index(const uint8_t *serialized, uint16_t total_serialized_len,
                                               int &deserialized_len, int32_t idx) {
    auto serialize_len = total_serialized_len - (FIXED_PART_LEN - INDEX_LEN);
    auto *deserialized = new uint8_t[total_serialized_len / 3 * 4 + 16];
    // 1st: deserialize preparation: base64 encoding
#ifdef __AVX2__
    size_t length = fast_avx2_base64_encode(reinterpret_cast<char *>(deserialized),
                                            reinterpret_cast<const char *>(serialized), serialize_len);
#else
    size_t length = SERIAL_ENCODE(reinterpret_cast<char *>(deserialized),
                                  reinterpret_cast<const char *>(serialized), serialize_len);

#endif
    // 2nd: skip padding (padding could be 'A'-'Z', '+', '/', '=')
    for (; deserialized[length - 1] >= 'A' && deserialized[length - 1] <= 'Z' && length >= 0; length--) {}

    // 3rd: append other info
    size_t offset = length;
    memcpy(deserialized + offset, serialized + serialize_len, BASE64_INFO_LEN);
    offset += BASE64_INFO_LEN;
    memcpy(deserialized + offset, &idx, sizeof(int32_t));
    offset += INDEX_LEN;
    memcpy(deserialized + offset, serialized + serialize_len + BASE64_INFO_LEN, VARYING_VERIFY_LEN);

    // 4th: assign the correct length
    deserialized_len = length + FIXED_PART_LEN;
    return deserialized;
}
// ------------------------------ End of Base36, do not support A-Z yet --------------------------------------------

int serialize_base36_decoding_with_padding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized) {
    auto serialize_len = len - FIXED_PART_LEN;

    // 1st: fallback to normal cases when `serialize_len >= FIXED_BASES_SLOT_LEN`
    if (serialize_len >= FIXED_BASES_SLOT_LEN) {
        return serialize_base36_decoding_skip_index(message, len, serialized);
    }

    // 2nd: handle smaller messages
    size_t estimated_length = FIXED_BASES_SLOT_LEN / 4 * 3;
    memcpy(serialized + estimated_length, message + serialize_len, BASE64_INFO_LEN);
    memcpy(serialized + estimated_length + BASE64_INFO_LEN, message + serialize_len + BASE64_INFO_LEN + INDEX_LEN,
           VARYING_VERIFY_LEN);

    uint8_t local_storage[FIXED_BASES_SLOT_LEN];
    memset(local_storage, 'B', FIXED_BASES_SLOT_LEN);
    memcpy(local_storage, message, serialize_len);

#ifdef __AVX2__
    fast_avx2_base64_decode(reinterpret_cast<char *>(serialized),
                                            reinterpret_cast<const char *>(local_storage), FIXED_BASES_SLOT_LEN);
#else
    SERIAL_DECODE(reinterpret_cast<char *>(serialized),
                  reinterpret_cast<const char *>(local_storage), FIXED_BASES_SLOT_LEN);
#endif
    return estimated_length + FIXED_PART_LEN - INDEX_LEN;
}

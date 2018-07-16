#include <cstdint>
#include <cstring>

#include "serialization.h"
#include "../fast_base64/fastavxbase64.h"
#include "../naive_base64/naive_base64.h"

#define SERIAL_DECODE chromium_base64_decode
#define SERIAL_ENCODE chromium_base64_encode
//#define SERIAL_DECODE naive_base64_decode
//#define SERIAL_ENCODE naive_base64_encode

//#undef __AVX2__

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

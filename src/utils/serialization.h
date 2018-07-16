#ifndef QUEUERACE_SERIALIZATION_H
#define QUEUERACE_SERIALIZATION_H

#define BASE64_INFO_LEN (2u)
#define INDEX_LEN (4u)
#define VARYING_VERIFY_LEN (4u)
#define FIXED_PART_LEN (10u)

int serialize_base64_decoding_general(uint8_t *message, uint16_t len, uint8_t *serialized);

uint8_t *deserialize_base64_encoding_general(const uint8_t *serialized, uint16_t total_serialized_len, int &len);

// 1st: basic usage of base64 encoding and decoding for deserialization and serialization
int serialize_base64_decoding(uint8_t *message, uint16_t len, uint8_t *serialized);

uint8_t *deserialize_base64_encoding(const uint8_t *serialized, uint16_t total_serialized_len, int &len);

// 2nd: skip index optimization
int serialize_base64_decoding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized);

// 2.1 attention: new[] inside
uint8_t *deserialize_base64_encoding_add_index(const uint8_t *serialized, uint16_t total_serialized_len,
                                               int &deserialized_len, int32_t idx);

// 2.2 not able to use in the current testing environment
void deserialize_base64_encoding_add_index_in_place(const uint8_t *serialized, uint16_t total_serialized_len,
                                                    uint8_t *deserialized, int &deserialized_len, int32_t idx);

// 3rd: base36 (a-z, 0-9), other numbers can be used for magic codes
int serialize_base36_decoding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized);

uint8_t *deserialize_base36_encoding_add_index(const uint8_t *serialized, uint16_t total_serialized_len,
                                               int &deserialized_len, int32_t idx);

// 4th: base36 supporting small message
#define FIXED_BASES_SLOT_LEN 48

int serialize_base36_decoding_with_padding_skip_index(uint8_t *message, uint16_t len, uint8_t *serialized);

#endif //QUEUERACE_SERIALIZATION_H

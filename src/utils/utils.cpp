#include <cstdlib>
#include <cstring>

#include "utils.h"
#include "log.h"

int four_char_to_int(char *length) {
    int64_t len = 0;
    len |= ((length[0] & 0xff) << 24);
    len |= ((length[1] & 0xff) << 16);
    len |= ((length[2] & 0xff) << 8);
    len |= (length[3] & 0xff);
    return len;
}

void int_to_four_char(int32_t integer, char *bytes) {
    bytes[0] = (char) ((integer >> 24) & 0xFF);
    bytes[1] = (char) ((integer >> 16) & 0xFF);
    bytes[2] = (char) ((integer >> 8) & 0xFF);
    bytes[3] = (char) ((integer >> 0) & 0xFF);
}

void long_to_8bytes(int64_t integer, void *bytes) {
    unsigned char *b = (unsigned char *) bytes;
    unsigned char *p = (unsigned char *) &integer;
    memcpy(b, p, sizeof(unsigned char) * 8);
}

int64_t bytes8_to_long(void *bytes) {
    return *((int64_t *) bytes);
}
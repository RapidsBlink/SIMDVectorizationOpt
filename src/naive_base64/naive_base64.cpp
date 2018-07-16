#include <cstdlib>
#include <cstdint>

static const char base64_encoding_table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                               'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                               '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};


static const char base64_decoding_table[123] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59,
        60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
        43, 44, 45, 46, 47, 48, 49, 50, 51
};

#define CHARPAD '='

#define MODP_B64_ERROR ((size_t)-1)
#define BADCHAR 0x01FFFFFF

size_t naive_base64_encode(char *dest, const char *str, size_t len) {
    size_t i = 0;
    uint8_t *p = (uint8_t *) dest;

    /* unsigned here is important! */
    uint8_t t1, t2, t3;

    if (len > 2) {
        for (; i < len - 2; i += 3) {
            t1 = str[i];
            t2 = str[i + 1];
            t3 = str[i + 2];

            *p++ = base64_encoding_table[t1 >> 2];
            *p++ = base64_encoding_table[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
            *p++ = base64_encoding_table[((t2 & 0x0F) << 2) | ((t3 >> 6) & 0x03)];
            *p++ = base64_encoding_table[t3 & 0x3F];
        }
    }

    switch (len - i) {
        case 0:
            break;
        case 1:
            t1 = str[i];
            *p++ = base64_encoding_table[t1 >> 2];
            *p++ = base64_encoding_table[(t1 & 0x03) << 4];
            *p++ = CHARPAD;
            *p++ = CHARPAD;
            break;
        default: /* case 2 */
            t1 = str[i];
            t2 = str[i + 1];
            *p++ = base64_encoding_table[t1 >> 2];
            *p++ = base64_encoding_table[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
            *p++ = base64_encoding_table[(t2 & 0x0F) << 2];
            *p++ = CHARPAD;
    }

    *p = '\0';
    return p - (uint8_t *) dest;
}


size_t naive_base64_decode(char *dest, const char *src, size_t len) {
    if (len == 0) return 0;

#ifdef DOPAD
    /*
     * if padding is used, then the message must be at least
     * 4 chars and be a multiple of 4
     */
    if (len < 4 || (len % 4 != 0)) {
      return MODP_B64_ERROR; /* error */
    }
    /* there can be at most 2 pad chars at the end */
    if (src[len-1] == CHARPAD) {
        len--;
        if (src[len -1] == CHARPAD) {
            len--;
        }
    }
#endif

    size_t i;
    int leftover = len % 4;
    size_t chunks = (leftover == 0) ? len / 4 - 1 : len / 4;

    uint8_t *p = (uint8_t *) dest;
//    uint32_t x = 0;
    const uint8_t *y = (uint8_t *) src;
    for (i = 0; i < chunks; ++i, y += 4) {
//        x = d0[y[0]] | d1[y[1]] | d2[y[2]] | d3[y[3]];
//        if (x >= BADCHAR) return MODP_B64_ERROR;
        auto d0 = (uint8_t) base64_decoding_table[y[0]];
        auto d1 = (uint8_t) base64_decoding_table[y[1]];
        auto d2 = (uint8_t) base64_decoding_table[y[2]];
        auto d3 = (uint8_t) base64_decoding_table[y[3]];
        *p++ = (d0 << 2) | (d1 >> 4);
        *p++ = (d1 << 4) | (d2 >> 2);
        *p++ = (d2 << 6) | d3;
    }

    switch (leftover) {
        case 0:
//            x = d0[y[0]] | d1[y[1]] | d2[y[2]] | d3[y[3]];
//            if (x >= BADCHAR) return MODP_B64_ERROR;
        {
            auto d0 = (uint8_t) base64_decoding_table[y[0]];
            auto d1 = (uint8_t) base64_decoding_table[y[1]];
            auto d2 = (uint8_t) base64_decoding_table[y[2]];
            auto d3 = (uint8_t) base64_decoding_table[y[3]];
            *p++ = (d0 << 2) | (d1 >> 4);
            *p++ = (d1 << 4) | (d2 >> 2);
            *p++ = (d2 << 6) | d3;
        }
            return (chunks + 1) * 3;
        case 1:  /* with padding this is an impossible case */
        {

            auto d0 = (uint8_t) base64_decoding_table[y[0]];
            *p = (d0 << 2); // i.e. first char/byte in int
        }
            break;
        case 2: // * case 2, 1  output byte */
        {

            auto d0 = (uint8_t) base64_decoding_table[y[0]];
            auto d1 = (uint8_t) base64_decoding_table[y[1]];

            *p = (d0 << 2) | (d1 >> 4); // i.e. first char
        }

            break;
        default: /* case 3, 2 output bytes */
        {

            auto d0 = (uint8_t) base64_decoding_table[y[0]];
            auto d1 = (uint8_t) base64_decoding_table[y[1]];
            auto d2 = (uint8_t) base64_decoding_table[y[2]];  /* 0x3c */

            *p++ = (d0 << 2) | (d1 >> 4);
            *p = (d1 << 4) | (d2 >> 2);
        }

            break;
    }

//    if (x >= BADCHAR) return MODP_B64_ERROR;

    return 3 * chunks + (6 * leftover) / 8;
}
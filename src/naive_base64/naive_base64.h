#pragma once

size_t naive_base64_encode(char *dest, const char *str, size_t len);

size_t naive_base64_decode(char *dest, const char *src, size_t len);
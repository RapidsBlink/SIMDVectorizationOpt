#pragma once

int four_char_to_int(char *length);

void int_to_four_char(int32_t integer, char *bytes);

void long_to_8bytes(int64_t integer, void *bytes);

int64_t bytes8_to_long(void *bytes);

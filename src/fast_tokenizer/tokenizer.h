//
// Created by yche on 5/4/18.
//

#ifndef AGENT_TOKENIZER_H
#define AGENT_TOKENIZER_H

#include <cstdlib>

int serial_split(const char *str, short len, short *off);

int simd_split_efficient(char *str, short len, short *off);

int generate_body(char *res, char *str_buffer, short *off, short len_off);

void generate_header(char *res, int body_len, int64_t req_id);

int generate_res_in_place(char *res, char *str, short len, int64_t req_id);

int generate_res_in_place_hard_code(char *res, char *str, short len, int64_t req_id);

#endif //AGENT_TOKENIZER_H

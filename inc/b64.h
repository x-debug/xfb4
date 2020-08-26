//
// Created by nbboy on 2020/8/24.
//

#ifndef B64_B64_H
#define B64_B64_H

#include <unistd.h>

int b64_encode(const char *str, char *encoded, size_t encodedLen);
int b64_decode(const char *b64Str, char *decoded, size_t decodedLen);

#endif //B64_B64_H

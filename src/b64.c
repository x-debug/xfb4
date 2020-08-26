//
// Created by nbboy on 2020/8/24.
//

#include <string.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "b64.h"

typedef unsigned char byte;

static char B64_TABLE[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

static int _bytes_encode(const byte bytes[], size_t bLen, char *buffer, size_t bufferLen) {
    byte ch, temp, at;
    int i = 0;

    for (int j = 0; j < bLen; j += 3) {
        ch = bytes[j];
        temp = ch >> 2;
        buffer[i++] = B64_TABLE[temp];
        at = ((ch & 0x03) << 4) | (bytes[j + 1] >> 4);
        buffer[i++] = B64_TABLE[at];
        if (bytes[j + 1] == 0) {
            buffer[i++] = '=';
        } else {
            at = ((0x0F & bytes[j + 1]) << 2) | (bytes[j + 2] >> 6);
            buffer[i++] = B64_TABLE[at];
        }

        if (bytes[j + 2] == 0) {
            buffer[i++] = '=';
        } else {
            at = bytes[j + 2] & 0x3F;
            buffer[i++] = B64_TABLE[at];
        }
    }

    buffer[i++] = '\0';
    return i;
}

static byte _reverse_table(char c) {
    if (c == '+') {
        return 62;
    }

    if (c == '/') {
        return 63;
    }

    /* 0 ~ 9 */
    if (c >= 48 && c <= 57) {
        return c + 4;
    }

    /* A ~ Z */
    if (c >= 65 && c <= 90) {
        return c - 65;
    }

    /* a ~ z */
    if (c >= 97 && c <= 122) {
        return c - 71;
    }

    return 0;
}

static int _bytes_decode(const char *str, size_t bLen, char *buffer, size_t bufferLen) {
    byte ch, temp, at;
    int i = 0;

    for (int j = 0; j < bLen; j += 4) {
        ch = _reverse_table(str[j]);
        ch = (ch << 2) | (_reverse_table(str[j+1]) >> 4);
        buffer[i++] = ch;

        ch = _reverse_table(str[j+1]) & 0x0F;
        ch = (ch << 4) | (_reverse_table(str[j+2]) >> 2);
        buffer[i++] = ch;

        ch = _reverse_table(str[j+2]) & 0x03;
        ch = (ch << 6) | _reverse_table(str[j+3]);
        buffer[i++] = ch;
    }

    buffer[i++] = '\0';
    return i;
}

int b64_encode(const char *str, char *encoded, size_t encodedLen) {
    size_t len = strlen(str);
    int alignedLen = (int) (ceil((double) len / 3) * 3);
    byte *aligned = malloc(alignedLen);
    bzero(aligned, alignedLen);
    memcpy(aligned, str, len);
    int ret = _bytes_encode(aligned, alignedLen, encoded, encodedLen);
    free(aligned);
    return ret;
}

int b64_decode(const char *b64Str, char *decoded, size_t decodedLen) {
    size_t len = strlen(b64Str);
    assert(len % 4 == 0);
    int ret = _bytes_decode(b64Str, len, decoded, decodedLen);
    return ret;
}


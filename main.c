#include <stdio.h>
#include <sys/time.h>
#include "b64.h"

int main() {
    struct timeval stv, etv;

    gettimeofday(&stv, NULL);
    for (int i = 0; i < 9000000; ++i) {
        char *str = "中华人民共和国万岁。!!hello,world,OMG";
        char buffer[256];
        char result[256];
        b64_encode(str, buffer, 256);
        b64_decode(buffer, result, 256);
    }
    gettimeofday(&etv, NULL);
    printf("%f second\r\n", (double )(etv.tv_sec - stv.tv_sec) + (double )(etv.tv_usec - stv.tv_usec)/1000000.0);
    return 0;
}

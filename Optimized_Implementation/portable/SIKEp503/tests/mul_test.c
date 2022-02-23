#include "../P503_internal.h"
#include "test_extras.h"
#include <stdio.h>

void phex(char *label, digit_t *x, unsigned int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++){
        digit_t d = x[i];
        for (int j = 0; j < 8; j++)
        {
            printf("%01x",d&0xf);
            d >>= 4;
        }
    }
    printf("\n");
}

#define NUM_MUL_TESTS 100
int main() {
    digit_t a[NWORDS_FIELD];
    digit_t b[NWORDS_FIELD];
    digit_t c[2*NWORDS_FIELD];
    digit_t c_check[2*NWORDS_FIELD];

    for (int i = 0; i < NUM_MUL_TESTS; i++) {
        // pick random a & b
        randombytes(a,sizeof(a));
        randombytes(b,sizeof(b));
        mp_mul(a,b,c,NWORDS_FIELD);
        mp_mul_comba(a,b,c_check,NWORDS_FIELD);
        int check = memcmp(c,c_check,NWORDS_FIELD*2);
        if (check) {
            printf("[!] Test %d did not pass!\n",i);
            phex("c_result",c,2*NWORDS_FIELD);
            phex("c_verify",c_check,2*NWORDS_FIELD);
            return FAILED;
        } else {
            printf("[+] Test %d did pass!\n",i);
        }
    }
    return PASSED;
}
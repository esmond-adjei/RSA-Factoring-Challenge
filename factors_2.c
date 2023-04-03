#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factorize(mpz_t n, mpz_t p, mpz_t q) {
    mpz_t i;
    mpz_init(i);
    mpz_set_ui(i, 2);
    mpz_sqrt(p, n);
    while (mpz_cmp(i, p) <= 0) {
        if (mpz_divisible_ui_p(n, mpz_get_ui(i))) {
            mpz_tdiv_q(q, n, i);
            return;
        }
        mpz_add_ui(i, i, 1);
    }
    mpz_set_ui(p, 0);
    mpz_set_ui(q, 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: factors <file>\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }
    char line[1024];
    mpz_t n, p, q;
    mpz_inits(n, p, q, NULL);
    while (fgets(line, sizeof(line), fp)) {
        mpz_set_str(n, line, 10);
        factorize(n, p, q);
        if (mpz_cmp_ui(p, 0) != 0 && mpz_cmp_ui(q, 0) != 0) {
            gmp_printf("%Zd=%Zd*%Zd\n", n, p, q);
        } else {
            gmp_printf("%Zd is prime\n", n);
        }
    }
    mpz_clears(n, p, q, NULL);
    fclose(fp);
    return 0;
}


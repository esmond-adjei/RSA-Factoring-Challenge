#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint64_t n;
    uint64_t p;
} factor_t;

void factorize(uint64_t n, factor_t* factors) {
    uint64_t i, j;
    factors->n = n;
    factors->p = 1;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors->p = i;
            factors->n /= i;
            return;
        }
    }
    factors->p = n;
    factors->n /= n;
}

int is_prime(uint64_t n) {
    uint64_t i;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        printf("where <file> is a file containing natural numbers to factor.\n");
        printf("One number per line\n");
        printf("You can assume that all lines will be valid natural numbers greater than 1\n");
        printf("You can assume that there will be no empty line, and no space before and after the valid number\n");
        printf("The file will always end with a new line\n");
        printf("Output format: n=p*q\n");
        printf("one factorization per line\n");
        printf("p and q don’t have to be prime numbers\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    uint64_t n;
    factor_t factors;

    while ((read = getline(&line, &len, fp)) != -1) {
        n = strtoull(line, NULL, 10);
        while (!is_prime(n)) {
            factorize(n, &factors);
            printf("%llu=%llu*%llu\n", n, factors.p, factors.n);
            n = factors.n;
        }
        if (n > 1) {
            printf("%llu is prime\n", n);
        }
    }

    if (line) {
        free(line);
    }
    fclose(fp);

    return 0;
}


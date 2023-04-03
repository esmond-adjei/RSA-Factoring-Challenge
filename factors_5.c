#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    uint64_t p; // smaller factor
    uint64_t n; // larger factor
} factors_t;

bool factorize(uint64_t n, factors_t *factors) {
    uint64_t i;
    uint64_t max_factor = sqrt(n);

    for (i = 2; i <= max_factor; i++) {
        if (n % i == 0) {
            factors->p = i;
            factors->n = n / i;
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    FILE *file;
    uint64_t n;
    factors_t factors;

    if (argc != 2) {
        printf("Usage: factors <file>\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return 1;
    }

    while (fscanf(file, "%llu", &n) != EOF) {
        if (factorize(n, &factors)) {
            printf("%lu=%lu*%lu\n", n, factors.n, factors.p);
        } else {
            printf("%lu is prime\n", n);
        }
    }

    fclose(file);
    return 0;
}


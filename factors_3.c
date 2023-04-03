#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorize(long long n, long long *p, long long *q) {
    if (n % 2 == 0) {
        *p = 2;
        *q = n / 2;
        return;
    }
    for (long long i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
    *p = n;
    *q = 1;
}

int is_prime(long long n) {
    if (n == 2) {
        return 1;
    }
    if (n < 2 || n % 2 == 0) {
        return 0;
    }
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (int i = 0; i < 5; i++) { // Perform 5 rounds of Miller-Rabin test
        long long a = rand() % (n - 1) + 1;
        long long x = pow(a, d);
        long long y = 0;
        for (int j = 0; j < s; j++) {
            y = pow(x, 2);
            if (y % n == 1 && x != 1 && x != n - 1) {
                return 0;
            }
            x = y;
        }
        if (y % n != 1) {
            return 0;
        }
    }
    return 1;
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
    while (fgets(line, sizeof(line), fp)) {
        long long n = atoll(line);
        long long p, q;
        factorize(n, &p, &q);
        if (is_prime(p) || is_prime(q)) {
            printf("%lld is prime\n", n);
        } else {
            printf("%lld=%lld*%lld\n", n, p, q);
        }
    }
    fclose(fp);
    return 0;
}


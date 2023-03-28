#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorize(long long n, long long *p, long long *q) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
    *p = 0;
    *q = 0;
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
        long long n = atoi(line);
        long long p, q;
        factorize(n, &p, &q);
        if (p != 0 && q != 0) {
            printf("%lld=%lld*%lld\n", n, p, q);
        } else {
            printf("%lld is prime\n", n);
        }
    }
    fclose(fp);
    return 0;
}


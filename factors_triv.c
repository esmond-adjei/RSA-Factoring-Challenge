#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorize(long long n, long long *p, long long *q) {
    *p = 0;
    *q = 0;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
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
	p = 0;
	q = 0;
        factorize(n, &p, &q);
        if (p != 0 && q != 0) {
            printf("%lld=%lld*%lld\n", n, q, p);
        } else {
            printf("%lld is prime\n", n);
        }
    }
    fclose(fp);
    return 0;
}


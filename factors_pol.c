#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long f(long long x, long long c, long long n)
{
    return (x * x + c) % n;
}

long long pollards_rho(long long n)
{
    srand(time(NULL));
    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x - y), n);
    }
    return g;
}

void factorize(long long n, long long *p, long long *q) {
    if (n == 1) {
        *p = n;
        *q = 1;
        return;
    }
    if (n % 2 == 0) {
        *p = 2;
        *q = n / 2;
        return;
    }
    *p = n;
    while (*p == n) {
        *p = pollards_rho(n);
    }
    *q = n / *p;
}

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    FILE *fp = fopen(argv[1], "r");
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        long long n = atoll(line);
        long long p, q;
        factorize(n, &p, &q);
        printf("%lld=%lld*%lld\n", n, q, p);
    }
    fclose(fp);
    return 0;
}


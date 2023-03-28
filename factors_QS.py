#!/usr/bin/python3

import math, sys

def factorize(n):
    if n % 2 == 0:
        return 2, n // 2

    # Find the factors using the Quadratic Sieve algorithm
    sqrt_n = int(math.sqrt(n))
    m = sqrt_n + 1
    while True:
        a = m * m - n
        factor = math.isqrt(a)  # int(sqrt(a))
        if factor * factor == a:
            break
        else:
            m += 1

    p = m - factor
    q = n // p
    return p, q


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: factors <file>")
        sys.exit(1)
    filename = sys.argv[1]
    with open(filename, 'r') as f:
        for line in f:
            n = int(line.strip())
            factors = factorize(n)
            if factors:
                print(f"{n}={factors[0]}*{factors[1]}")
            else:
                print(f"{n} is prime")

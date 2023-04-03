#!/usr/bin/python3
import sys
from sympy import factorint

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: factors <file>")
        sys.exit(1)
    filename = sys.argv[1]
    with open(filename, 'r') as f:
        for line in f:
            n = int(line.strip())
            factors = factorint(n)
            if len(factors) == 1:
                print(f"{n} is prime")
            else:
                sorted_factors = sorted(factors.items())
                factor_strs = [f"{f[0]}^{f[1]}" for f in sorted_factors]
                print(f"{n}={','.join(factor_strs)}")


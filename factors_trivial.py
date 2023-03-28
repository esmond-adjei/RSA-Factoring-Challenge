#!/usr/bin/python3
import sys
from math import sqrt

def factorize(n):
	for i in range(2, int(sqrt(n)+1)):
		if n % i == 0:
			return n//i, i
	return 1, n

if __name__ == '__main__':
    filename = sys.argv[1]
    with open(filename, 'r') as f:
        for line in f:
            n = int(line.strip())
            p, q = factorize(n)
            print(f'{n}={p}*{q}')


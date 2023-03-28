#!/usr/bin/python3
from sys import argv
from math import  gcd
from random import randint

def pollards_rho(n):
	x = randint(2, n - 1)
	y = x
	c = randint(1, n - 1)
	g = 1

	while g == 1:
		x = (x * x + c) % n
		y = (y * y + c) % n
		g = gcd(abs(x - y), n)
	return g

def factorize(n):
	if n == 1:
		return n, 1
	if n % 2 == 0:
		return 2, n // 2
	p = n
	while p == n:
		p = pollards_rho(n)
	return p, n // p

if __name__ == '__main__':
	filename = argv[1]
	with open(filename, 'r') as f:
		for line in f:
			n = int(line.strip())
			p, q = factorize(n)
			print(f"{n}={p}*{q}")


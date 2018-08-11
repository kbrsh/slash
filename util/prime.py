import numpy as np

first = "101001111"

def isPrime(n):
    if n == 1:
        return False

    if n % 2 == 0:
        return False;

    i = 3

    while i * i <= n:
        if n % i == 0:
            return False

        i += 2

        if i > (2 ** 20):
            return True

    return True

def get():
    while True:
        bits = np.random.permutation(np.concatenate((np.zeros(32 - first.count("0"), dtype=int), np.ones(32 - first.count("1"), dtype=int))))

        prime = int(first + "".join(map(str, bits)), 2)

        if bits[len(bits) - 1] != 0 and isPrime(prime):
            return "{0:x}".format(prime).upper()

print(get())
print(get())

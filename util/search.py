import numpy as np
import itertools

def H(k):
    c = 2 ** k
    if c == 1:
        return np.matrix([
            [1]
        ])
    elif c == 2:
        return np.matrix([
            [1, 1],
            [1, -1]
        ])
    else:
        return np.kron(
            np.matrix([
                [1, 1],
                [1, -1]
            ]),
            H(k - 1)
        )

k = 3
t = 2
count = 0
Hk = H(k)

def randf():
    return np.matrix([list(np.random.permutation(np.concatenate((np.zeros(2 ** (k - 1), dtype=int), np.ones(2 ** (k - 1), dtype=int)))))])

def search(f):
    global count
    fs = []
    for bit in range(2 ** k):
        for bbit in range(2 ** k):
            new = np.copy(f)

            if new[0, bit] == 0:
                if new[0, bbit] == 1:
                    new[0, bit] = 1
                    new[0, bbit] = 0
                else:
                    continue
            else:
                if new[0, bbit] == 0:
                    new[0, bit] = 0
                    new[0, bbit] = 1
                else:
                    continue

            r = np.dot(new, Hk)
            nl = np.amax(np.abs(np.delete(r[0], 0)))
            fs.append((nl, new))

    maximum = 0

    for nl, fc in fs:
        if nl > maximum or nl == t:
            maximum = nl

    print("nl " + str(maximum) + "/" + str(t))

    for nl, fc in fs:
        if nl == maximum:
            if nl == t and (fc == 0).sum() == (2 ** (k - 1)) and (fc == 1).sum() == (2 ** (k - 1)):
                return fc[0].tolist()
            elif nl > t:
                return search(randf())
            else:
                return search(fc)

def isBijective(fs):
    fst = np.transpose(fs).tolist()
    for i, f in enumerate(fst[:-1]):
        for j in range(i + 1, len(fst) - 1):
            equal = True

            for bits in zip(f, fst[j]):
                b0, b1 = bits
                if b0 != b1:
                    equal = False

            if equal:
                return False

    return True

fs = []

for i in range(k):
    fs.append(search(randf()))

while not isBijective(fs):
    fs[round(np.random.rand() * (k - 1))] = search(randf())

print(fs)

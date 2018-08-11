import numpy as np

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

k = 8
Hk = H(k)

def random():
    return np.random.permutation(2 ** k)

def nonlinearity(solution):
    nonlinearities = np.empty(k, dtype=int)
    fs = np.empty((k, 2 ** k))

    for fvIndex, fv in enumerate(solution):
        digits = format(fv, "0" + str(k) + "b")

        for digitIndex in range(k):
            digit = 0

            if digitIndex < len(digits):
                if digits[digitIndex] == "0":
                    digit = 0
                else:
                    digit = 1

            fs[digitIndex, fvIndex] = digit

    for fIndex, f in enumerate(fs):
        nonlinearities[fIndex] = (2 ** (k - 1)) - np.amax(np.abs(np.delete(np.dot(f, Hk)[0], 0)))

    return nonlinearities

def search():
    a = 1
    solution = np.random.permutation(2 ** k)
    solutionNL = nonlinearity(solution)

    while np.any(solutionNL < ((2 ** (k - 1)) - (2 * k) - 2)):
        maxCandidate = None
        maxNL = 0

        for i in range(15):
            swaps = np.random.randint(len(solution), size=a + 1)

            for swapIndex in range(len(swaps) - 1):
                swap = swaps[swapIndex]
                swapNext = swaps[swapIndex + 1]

                candidate = np.copy(solution)
                candidateTmp = candidate[swap]
                candidate[swap] = candidate[swapNext]
                candidate[swapNext] = candidateTmp

                candidateNL = nonlinearity(candidate)

                if np.all(candidateNL >= maxNL):
                    maxCandidate = candidate
                    maxNL = candidateNL

        if maxNL.sum() > solutionNL.sum():
            print("move", solutionNL, "->", maxNL)
            solution = maxCandidate
            solutionNL = nonlinearity(solution)
            a = 1
        else:
            a = a + 1

    print(solution, solutionNL)

search()

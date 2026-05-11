P = [[] for _ in range(10)]
for k in range(1, 10):
    l = (10 ** (k - 1) - 1).bit_length()
    r = (10 ** k - 1).bit_length()
    P[k] = [1 << i for i in range(l, r)]

X = [set() for _ in range(10)]
X[0] = {0}

A = []

for k in range(1, 10):
    for i in range(1, k + 1):
        X[k] |= {x * (10 ** i) + p for x in X[k - i] for p in P[i]}
    A += list(X[k])

A.sort()

N = int(input())
print(A[N - 1])
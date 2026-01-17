import random

def bruteforce(n: int, a: list) -> bool:
    for i in range(n):
        for j in range(i+1, n):
            for k in range(j+1, n):
                if a[j] > a[i] and a[j] > a[k]:
                    return True 
    return False


NUM_TESTS = 5000
with open("input.txt", "w") as infile:
    infile.write(f"{NUM_TESTS}\n")

for i in range(NUM_TESTS):
    print("Test case", i+1)

    n = random.randint(2, 10)
    # generate random list
    l = [random.randint(1, 10000) for _ in range(n)]

    # append to input and output files
    with open("input.txt", "a") as infile:
        infile.write(f"{n}\n")
        infile.write(" ".join(map(str, l)) + "\n")

    with open("output.txt", "a") as outfile:
        outfile.write(bruteforce(n, l) and "True\n" or "False\n")
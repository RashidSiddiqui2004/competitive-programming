# 1. Print the sum of numbers from 1 to 100.
# print(sum([x for x in range(1, 101)]))

# 2. Find the maximum of three numbers stored in variables a, b, and c.
# a,b,c=10,20,30
# print(max(a, b, c))

# 3. Check if a number n is even or odd.
# num=1001
# print("Even" if num % 2 == 0 else "Odd")

# 4. Reverse a string s
# s = "reverse"
# print(''.join([s[len(s)-i-1] for i in range(len(s))]))
# print(s[::-1])

# 5. Count vowels in a string s.
# str = "reverse_vowels"
# print(sum([1 if ch in "aeiou" else 0 for ch in str]))
# Better, in operator already returns 0/1, so no need to specify it
# print(sum(ch in "aeiou" for ch in str))

# 6. Find factorial of a number n.
# n= 10
# import math; print(math.factorial(n))
# from functools import reduce; print(reduce(lambda x, y: x * y, range(1, n + 1)))


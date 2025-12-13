# 1. Print all even numbers from a list nums.
nums = [1,2,3,4,9,10,33,23,44,89]
# Prints as a list
print([x for x in nums if x % 2 == 0])
# If you wanted to print them space-separated (instead of a list), 
# you could do:
print(*[x for x in nums if x % 2 == 0])

# 2. Check if all elements in a list are unique.
l1 = [1,2,3,4,5,4]
print(len(l1)==len(set(l1)))

# 3. Compute the dot product of two lists a and b.
a1, a2 = [1,2,4], [3,4,5]
print(sum(a1[i]*a2[i] for i in range(len(a1))))

# 4. Find the most frequent word in a string text.
text = "hello ji, nice to meet you, hello agin, bye bye,"


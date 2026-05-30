# Compile: python3 control_flow.py
# Output:
# [2, 3, 5, 7, 11, 13, 17, 19]
# pass

def is_prime(n: int) -> bool:
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            break
    else:
        return True  # for/else: runs only if loop wasn't broken
    return False

primes = [x for x in range(2, 20) if is_prime(x)]
print(primes)

# Conditional expression (ternary)
score = 85
grade = "pass" if score >= 60 else "fail"
print(grade)

# while loop
count = 0
while count < 3:
    count += 1

# Nested conditions
x = 42
if x < 0:
    print("negative")
elif x == 0:
    print("zero")
else:
    print("positive")

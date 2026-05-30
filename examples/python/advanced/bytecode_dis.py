# Compile: python3 bytecode_dis.py
# Output:
# Bytecode for factorial printed

import dis

def factorial(n: int) -> int:
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

print("=== Bytecode for factorial ===")
dis.dis(factorial)
print(f"\nConstants:  {factorial.__code__.co_consts}")
print(f"Locals:     {factorial.__code__.co_varnames}")
print(f"Stack size: {factorial.__code__.co_stacksize}")

# Compare optimized vs unoptimized code
def slow_concat(items):
    result = ""
    for item in items:
        result = result + str(item)  # Creates new string each iteration
    return result

def fast_concat(items):
    return "".join(str(item) for item in items)

print("\n=== slow_concat instruction count ===")
instructions = list(dis.get_instructions(slow_concat))
print(f"  {len(instructions)} instructions")

print("\n=== fast_concat instruction count ===")
instructions = list(dis.get_instructions(fast_concat))
print(f"  {len(instructions)} instructions")

import timeit
n = 1000
items = range(n)
slow = timeit.timeit("slow_concat(items)", globals=locals(), number=100)
fast = timeit.timeit("fast_concat(items)", globals=locals(), number=100)
print(f"\nspeedup: {slow/fast:.1f}x faster with join")

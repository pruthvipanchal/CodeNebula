# Compile: python3 unittest_basics.py
# Output:
# ....
# OK

import unittest
from functools import lru_cache

@lru_cache
def factorial(n: int) -> int:
    if n < 0:
        raise ValueError(f"Factorial undefined for {n}")
    if not isinstance(n, int):
        raise TypeError(f"Expected int, got {type(n).__name__}")
    return 1 if n == 0 else n * factorial(n - 1)

class TestFactorial(unittest.TestCase):
    def test_base_cases(self):
        self.assertEqual(factorial(0), 1)
        self.assertEqual(factorial(1), 1)

    def test_positive(self):
        self.assertEqual(factorial(5), 120)
        self.assertEqual(factorial(10), 3628800)

    def test_negative_raises(self):
        with self.assertRaises(ValueError):
            factorial(-1)

    def test_large(self):
        self.assertGreater(factorial(20), factorial(19))

if __name__ == "__main__":
    unittest.main(verbosity=1)
